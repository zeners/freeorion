
#ifndef _ClientEmpireManager_h_
#include "ClientEmpireManager.h"
#endif

#ifndef _XMLObjectFactory_h_
#include "../GG/XML/XMLObjectFactory.h"
#endif

#ifndef _SitRepEntry_h_
#include "../util/SitRepEntry.h"
#endif

#include <string>


ClientEmpireManager::ClientEmpireManager()
{
    // no worries yet
}
   
/**
*  Handles an update for this client.  
*  The XMLElement should be an XMLDiff for the empires in this client
*  manager (that is, produced by ServerEmpireManager::CreateClientEmpireUpdate()
*
*/
bool ClientEmpireManager::HandleEmpireElementUpdate( GG::XMLElement empireElement)
{
    // FINISH ME!
    return true;
}

/**
*  Takes an XMLElement representing a list of sitrep events
*  The list will be decoded, one entry at a time, and the entries
*  will be added to the sitrep of the empire to whom they belong.
* 
*  The XMLElement passed into this method should be identical to
*  that generated by ServerEmpireManager::CreateClientSitrepUpdate()
*
*/
bool ClientEmpireManager::HandleSitRepElementUpdate( GG::XMLElement sitRepElement)
{
    std::string sID = (sitRepElement.Attribute("EmpireID"));
    
    if( sID == "" )
    {
        return false;
    }
    
    int iID = atoi(sID.c_str());
    
    Empire* emp = Lookup(iID);
    if(emp == NULL)
    {
        return false;
    }
    
    emp->ClearSitRep();
    
    // make object factory for sitrep entries
    GG::XMLObjectFactory<SitRepEntry> sitrep_factory;
    SitRepEntry::InitObjectFactory(sitrep_factory);
    
    GG::XMLElement sitrep = sitRepElement.Child("m_sitrep_entries");
    for(unsigned int i=0; i<sitrep.NumChildren(); i++)
    {
        emp->AddSitRepEntry( sitrep_factory.GenerateObject(sitrep.Child(i)) );
    }
        
    return true;
}
