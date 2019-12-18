#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ieee80211_device {int* Regdot11HTOperationalRateSet; int /*<<< orphan*/  dev; scalar_t__ (* GetHalfNmodeSupportByAPsHandler ) (int /*<<< orphan*/ ) ;TYPE_1__* pHTInfo; } ;
struct TYPE_4__ {int ChlWidth; int ShortGI20Mhz; int ShortGI40Mhz; int TxSTBC; int MaxAMSDUSize; int DssCCk; int MPDUDensity; int MaxRxAMPDUFactor; int* MCS; int ExtHTCapInfo; int* TxBFCap; scalar_t__ ASCap; scalar_t__ LSigTxopProtect; scalar_t__ PSMP; scalar_t__ DelayBA; scalar_t__ RxSTBC; scalar_t__ GreenField; int /*<<< orphan*/  MimoPwrSave; scalar_t__ AdvCoding; } ;
struct TYPE_3__ {scalar_t__ ePeerHTSpecVer; int IOTAction; scalar_t__ bRegSuppCCK; scalar_t__ bRegBW40MHz; int /*<<< orphan*/  SelfMimoPs; } ;
typedef  TYPE_1__* PRT_HIGH_THROUGHPUT ;
typedef  TYPE_2__* PHT_CAPABILITY_ELE ;
typedef  int /*<<< orphan*/  EWC11NHTCap ;

/* Variables and functions */
 int HT_IOT_ACT_DISABLE_ALL_2SS ; 
 int HT_IOT_ACT_DISABLE_MCS14 ; 
 int HT_IOT_ACT_DISABLE_MCS15 ; 
 scalar_t__ HT_SPEC_VER_EWC ; 
 int /*<<< orphan*/  IEEE80211_DEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  IEEE80211_DL_ERR ; 
 int /*<<< orphan*/  IEEE80211_DL_HT ; 
 int MAX_RECEIVE_BUFFER_SIZE ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ) ; 

void HTConstructCapabilityElement(struct ieee80211_device* ieee, u8* posHTCap, u8* len, u8 IsEncrypt)
{
	PRT_HIGH_THROUGHPUT	pHT = ieee->pHTInfo;
	PHT_CAPABILITY_ELE 	pCapELE = NULL;
	//u8 bIsDeclareMCS13;

	if ((posHTCap == NULL) || (pHT == NULL))
	{
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "posHTCap or pHTInfo can't be null in HTConstructCapabilityElement()\n");
		return;
	}
	memset(posHTCap, 0, *len);
	if(pHT->ePeerHTSpecVer == HT_SPEC_VER_EWC)
	{
		u8	EWC11NHTCap[] = {0x00, 0x90, 0x4c, 0x33};	// For 11n EWC definition, 2007.07.17, by Emily
		memcpy(posHTCap, EWC11NHTCap, sizeof(EWC11NHTCap));
		pCapELE = (PHT_CAPABILITY_ELE)&(posHTCap[4]);
	}else
	{
		pCapELE = (PHT_CAPABILITY_ELE)posHTCap;
	}


	//HT capability info
	pCapELE->AdvCoding 		= 0; // This feature is not supported now!!
	if(ieee->GetHalfNmodeSupportByAPsHandler(ieee->dev))
	{
		pCapELE->ChlWidth = 0;
	}
	else
	{
		pCapELE->ChlWidth = (pHT->bRegBW40MHz?1:0);
	}

//	pCapELE->ChlWidth 		= (pHT->bRegBW40MHz?1:0);
	pCapELE->MimoPwrSave 		= pHT->SelfMimoPs;
	pCapELE->GreenField		= 0; // This feature is not supported now!!
	pCapELE->ShortGI20Mhz		= 1; // We can receive Short GI!!
	pCapELE->ShortGI40Mhz		= 1; // We can receive Short GI!!
	//DbgPrint("TX HT cap/info ele BW=%d SG20=%d SG40=%d\n\r",
		//pCapELE->ChlWidth, pCapELE->ShortGI20Mhz, pCapELE->ShortGI40Mhz);
	pCapELE->TxSTBC 		= 1;
	pCapELE->RxSTBC 		= 0;
	pCapELE->DelayBA		= 0;	// Do not support now!!
	pCapELE->MaxAMSDUSize	= (MAX_RECEIVE_BUFFER_SIZE>=7935)?1:0;
	pCapELE->DssCCk 		= ((pHT->bRegBW40MHz)?(pHT->bRegSuppCCK?1:0):0);
	pCapELE->PSMP			= 0; // Do not support now!!
	pCapELE->LSigTxopProtect	= 0; // Do not support now!!


	//MAC HT parameters info
        // TODO: Nedd to take care of this part
	IEEE80211_DEBUG(IEEE80211_DL_HT, "TX HT cap/info ele BW=%d MaxAMSDUSize:%d DssCCk:%d\n", pCapELE->ChlWidth, pCapELE->MaxAMSDUSize, pCapELE->DssCCk);

	if( IsEncrypt)
	{
		pCapELE->MPDUDensity 	= 7; // 8us
		pCapELE->MaxRxAMPDUFactor 	= 2; // 2 is for 32 K and 3 is 64K
	}
	else
	{
		pCapELE->MaxRxAMPDUFactor 	= 3; // 2 is for 32 K and 3 is 64K
		pCapELE->MPDUDensity 	= 0; // no density
	}

	//Supported MCS set
	memcpy(pCapELE->MCS, ieee->Regdot11HTOperationalRateSet, 16);
	if(pHT->IOTAction & HT_IOT_ACT_DISABLE_MCS15)
		pCapELE->MCS[1] &= 0x7f;

	if(pHT->IOTAction & HT_IOT_ACT_DISABLE_MCS14)
		pCapELE->MCS[1] &= 0xbf;

	if(pHT->IOTAction & HT_IOT_ACT_DISABLE_ALL_2SS)
		pCapELE->MCS[1] &= 0x00;

	// 2008.06.12
	// For RTL819X, if pairwisekey = wep/tkip, ap is ralink, we support only MCS0~7.
	if(ieee->GetHalfNmodeSupportByAPsHandler(ieee->dev))
	{
		int i;
		for(i = 1; i< 16; i++)
			pCapELE->MCS[i] = 0;
	}

	//Extended HT Capability Info
	memset(&pCapELE->ExtHTCapInfo, 0, 2);


	//TXBF Capabilities
	memset(pCapELE->TxBFCap, 0, 4);

	//Antenna Selection Capabilities
	pCapELE->ASCap = 0;
//add 2 to give space for element ID and len when construct frames
	if(pHT->ePeerHTSpecVer == HT_SPEC_VER_EWC)
		*len = 30 + 2;
	else
		*len = 26 + 2;



//	IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA | IEEE80211_DL_HT, posHTCap, *len -2);

	//Print each field in detail. Driver should not print out this message by default
//	HTDebugHTCapability(posHTCap, (u8*)"HTConstructCapability()");
	return;

}