#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_9__ {scalar_t__ bdRT2RTAggregation; } ;
struct TYPE_10__ {TYPE_1__ bssht; } ;
struct ieee80211_device {scalar_t__ pairwise_key_type; int /*<<< orphan*/  HTHighestOperaRate; int /*<<< orphan*/  HTCurrentOperaRate; int /*<<< orphan*/  dot11HTOperationalRateSet; TYPE_2__ current_network; TYPE_3__* pHTInfo; } ;
struct TYPE_14__ {int Length; } ;
struct TYPE_13__ {int ShortGI20Mhz; int ShortGI40Mhz; int DssCCk; scalar_t__ MaxAMSDUSize; scalar_t__ MaxRxAMPDUFactor; int MPDUDensity; int* MCS; scalar_t__ MimoPwrSave; scalar_t__ ChlWidth; } ;
struct TYPE_12__ {int RecommemdedTxWidth; int /*<<< orphan*/  OptMode; scalar_t__ ExtChlOffset; } ;
struct TYPE_11__ {int bCurrentHTSupport; int bCurTxBW40MHz; int bCurShortGI20MHz; int bCurShortGI40MHz; int bCurSuppCCK; int nAMSDU_MaxSize; int nCurrent_AMSDU_MaxSize; int bCurrentAMPDUEnable; int bAMPDUEnable; scalar_t__ AMPDU_Factor; scalar_t__ CurrentAMPDUFactor; int MPDU_Density; int CurrentMPDUDensity; int ForcedAMSDUMaxSize; scalar_t__ PeerMimoPs; int /*<<< orphan*/  CurrentOpMode; int /*<<< orphan*/  bRegRxReorderEnable; int /*<<< orphan*/  bCurRxReorderEnable; int /*<<< orphan*/  IOTAction; int /*<<< orphan*/  ForcedAMSDUMode; int /*<<< orphan*/  bRegRT2RTAggregation; int /*<<< orphan*/  bAMSDU_Support; int /*<<< orphan*/  bCurrent_AMSDU_Support; scalar_t__ bRegSuppCCK; scalar_t__ bRegShortGI40MHz; scalar_t__ bRegShortGI20MHz; int /*<<< orphan*/ * PeerHTInfoBuf; int /*<<< orphan*/ * PeerHTCapBuf; } ;
typedef  TYPE_3__* PRT_HIGH_THROUGHPUT ;
typedef  TYPE_4__* PHT_INFORMATION_ELE ;
typedef  TYPE_5__* PHT_CAPABILITY_ELE ;
typedef  int /*<<< orphan*/  HT_EXTCHNL_OFFSET ;
typedef  int /*<<< orphan*/  HT_CHANNEL_WIDTH ;
typedef  int /*<<< orphan*/  HT_CAPABILITY_ELE ;
typedef  int /*<<< orphan*/  EWC11NHTInfo ;
typedef  int /*<<< orphan*/  EWC11NHTCap ;

/* Variables and functions */
 int /*<<< orphan*/  EID_Vendor ; 
 int /*<<< orphan*/  HTFilterMCSRate (struct ieee80211_device*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTGetHighestMCSRate (struct ieee80211_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  HTSetConnectBwMode (struct ieee80211_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HT_AGG_FORCE_ENABLE ; 
 scalar_t__ HT_AGG_SIZE_32K ; 
 scalar_t__ HT_AGG_SIZE_64K ; 
 int /*<<< orphan*/  HT_IOT_ACT_TX_USE_AMSDU_8K ; 
 int /*<<< orphan*/  IEEE80211_DEBUG (int,char*) ; 
 int /*<<< orphan*/  IEEE80211_DEBUG_DATA (int,TYPE_5__*,int) ; 
 int IEEE80211_DL_DATA ; 
 int IEEE80211_DL_ERR ; 
 int IEEE80211_DL_HT ; 
 scalar_t__ KEY_TYPE_NA ; 
 int* MCS_FILTER_1SS ; 
 int* MCS_FILTER_ALL ; 
 scalar_t__ MIMO_PS_STATIC ; 
 int /*<<< orphan*/  OUI_SUBTYPE_DONT_CARE ; 
 int /*<<< orphan*/  OUI_SUB_REALTEK_AGG ; 
 TYPE_6__ PacketGetElement (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asocpdu ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int*,int) ; 
 TYPE_6__ osTmp ; 

void HTOnAssocRsp(struct ieee80211_device *ieee)
{
	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;
	PHT_CAPABILITY_ELE		pPeerHTCap = NULL;
	PHT_INFORMATION_ELE		pPeerHTInfo = NULL;
	u16	nMaxAMSDUSize = 0;
	u8*	pMcsFilter = NULL;

	static u8				EWC11NHTCap[] = {0x00, 0x90, 0x4c, 0x33};		// For 11n EWC definition, 2007.07.17, by Emily
	static u8				EWC11NHTInfo[] = {0x00, 0x90, 0x4c, 0x34};	// For 11n EWC definition, 2007.07.17, by Emily

	if( pHTInfo->bCurrentHTSupport == false )
	{
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "<=== HTOnAssocRsp(): HT_DISABLE\n");
		return;
	}
	IEEE80211_DEBUG(IEEE80211_DL_HT, "===> HTOnAssocRsp_wq(): HT_ENABLE\n");
//	IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA, pHTInfo->PeerHTCapBuf, sizeof(HT_CAPABILITY_ELE));
//	IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA, pHTInfo->PeerHTInfoBuf, sizeof(HT_INFORMATION_ELE));

//	HTDebugHTCapability(pHTInfo->PeerHTCapBuf,"HTOnAssocRsp_wq");
//	HTDebugHTInfo(pHTInfo->PeerHTInfoBuf,"HTOnAssocRsp_wq");
	//
	if(!memcmp(pHTInfo->PeerHTCapBuf,EWC11NHTCap, sizeof(EWC11NHTCap)))
		pPeerHTCap = (PHT_CAPABILITY_ELE)(&pHTInfo->PeerHTCapBuf[4]);
	else
		pPeerHTCap = (PHT_CAPABILITY_ELE)(pHTInfo->PeerHTCapBuf);

	if(!memcmp(pHTInfo->PeerHTInfoBuf, EWC11NHTInfo, sizeof(EWC11NHTInfo)))
		pPeerHTInfo = (PHT_INFORMATION_ELE)(&pHTInfo->PeerHTInfoBuf[4]);
	else
		pPeerHTInfo = (PHT_INFORMATION_ELE)(pHTInfo->PeerHTInfoBuf);


	////////////////////////////////////////////////////////
	// Configurations:
	////////////////////////////////////////////////////////
	IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA|IEEE80211_DL_HT, pPeerHTCap, sizeof(HT_CAPABILITY_ELE));
//	IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA|IEEE80211_DL_HT, pPeerHTInfo, sizeof(HT_INFORMATION_ELE));
	// Config Supported Channel Width setting
	//
	HTSetConnectBwMode(ieee, (HT_CHANNEL_WIDTH)(pPeerHTCap->ChlWidth), (HT_EXTCHNL_OFFSET)(pPeerHTInfo->ExtChlOffset));

//	if(pHTInfo->bCurBW40MHz == true)
		pHTInfo->bCurTxBW40MHz = ((pPeerHTInfo->RecommemdedTxWidth == 1)?true:false);

	//
	// Update short GI/ long GI setting
	//
	// TODO:
	pHTInfo->bCurShortGI20MHz=
		((pHTInfo->bRegShortGI20MHz)?((pPeerHTCap->ShortGI20Mhz==1)?true:false):false);
	pHTInfo->bCurShortGI40MHz=
		((pHTInfo->bRegShortGI40MHz)?((pPeerHTCap->ShortGI40Mhz==1)?true:false):false);

	//
	// Config TX STBC setting
	//
	// TODO:

	//
	// Config DSSS/CCK  mode in 40MHz mode
	//
	// TODO:
	pHTInfo->bCurSuppCCK =
		((pHTInfo->bRegSuppCCK)?((pPeerHTCap->DssCCk==1)?true:false):false);


	//
	// Config and configure A-MSDU setting
	//
	pHTInfo->bCurrent_AMSDU_Support = pHTInfo->bAMSDU_Support;

	nMaxAMSDUSize = (pPeerHTCap->MaxAMSDUSize==0)?3839:7935;

	if(pHTInfo->nAMSDU_MaxSize > nMaxAMSDUSize )
		pHTInfo->nCurrent_AMSDU_MaxSize = nMaxAMSDUSize;
	else
		pHTInfo->nCurrent_AMSDU_MaxSize = pHTInfo->nAMSDU_MaxSize;


	//
	// Config A-MPDU setting
	//
	pHTInfo->bCurrentAMPDUEnable = pHTInfo->bAMPDUEnable;

	// <1> Decide AMPDU Factor

	// By Emily
	if(!pHTInfo->bRegRT2RTAggregation)
	{
		// Decide AMPDU Factor according to protocol handshake
		if(pHTInfo->AMPDU_Factor > pPeerHTCap->MaxRxAMPDUFactor)
			pHTInfo->CurrentAMPDUFactor = pPeerHTCap->MaxRxAMPDUFactor;
		else
			pHTInfo->CurrentAMPDUFactor = pHTInfo->AMPDU_Factor;

	}else
	{
		// Set MPDU density to 2 to Realtek AP, and set it to 0 for others
		// Replace MPDU factor declared in original association response frame format. 2007.08.20 by Emily
#if 0
		osTmp= PacketGetElement( asocpdu, EID_Vendor, OUI_SUB_REALTEK_AGG, OUI_SUBTYPE_DONT_CARE);
		if(osTmp.Length >= 5)	//00:e0:4c:02:00
#endif
		if (ieee->current_network.bssht.bdRT2RTAggregation)
		{
			if( ieee->pairwise_key_type != KEY_TYPE_NA)
				// Realtek may set 32k in security mode and 64k for others
				pHTInfo->CurrentAMPDUFactor = pPeerHTCap->MaxRxAMPDUFactor;
			else
				pHTInfo->CurrentAMPDUFactor = HT_AGG_SIZE_64K;
		}else
		{
			if(pPeerHTCap->MaxRxAMPDUFactor < HT_AGG_SIZE_32K)
				pHTInfo->CurrentAMPDUFactor = pPeerHTCap->MaxRxAMPDUFactor;
			else
				pHTInfo->CurrentAMPDUFactor = HT_AGG_SIZE_32K;
		}
	}

	// <2> Set AMPDU Minimum MPDU Start Spacing
	// 802.11n 3.0 section 9.7d.3
#if 1
	if(pHTInfo->MPDU_Density > pPeerHTCap->MPDUDensity)
		pHTInfo->CurrentMPDUDensity = pHTInfo->MPDU_Density;
	else
		pHTInfo->CurrentMPDUDensity = pPeerHTCap->MPDUDensity;
	if(ieee->pairwise_key_type != KEY_TYPE_NA )
		pHTInfo->CurrentMPDUDensity 	= 7; // 8us
#else
	if(pHTInfo->MPDU_Density > pPeerHTCap->MPDUDensity)
		pHTInfo->CurrentMPDUDensity = pHTInfo->MPDU_Density;
	else
		pHTInfo->CurrentMPDUDensity = pPeerHTCap->MPDUDensity;
#endif
	// Force TX AMSDU

	// Lanhsin: mark for tmp to avoid deauth by ap from  s3
	//if(memcmp(pMgntInfo->Bssid, NETGEAR834Bv2_BROADCOM, 3)==0)
	if(0)
		{

			pHTInfo->bCurrentAMPDUEnable = false;
			pHTInfo->ForcedAMSDUMode = HT_AGG_FORCE_ENABLE;
			pHTInfo->ForcedAMSDUMaxSize = 7935;

		pHTInfo->IOTAction |=  HT_IOT_ACT_TX_USE_AMSDU_8K;
	}

	// Rx Reorder Setting
	pHTInfo->bCurRxReorderEnable = pHTInfo->bRegRxReorderEnable;

	//
	// Filter out unsupported HT rate for this AP
	// Update RATR table
	// This is only for 8190 ,8192 or later product which using firmware to handle rate adaptive mechanism.
	//

	// Handle Ralink AP bad MCS rate set condition. Joseph.
	// This fix the bug of Ralink AP. This may be removed in the future.
	if(pPeerHTCap->MCS[0] == 0)
		pPeerHTCap->MCS[0] = 0xff;

	HTFilterMCSRate(ieee, pPeerHTCap->MCS, ieee->dot11HTOperationalRateSet);

	//
	// Config MIMO Power Save setting
	//
	pHTInfo->PeerMimoPs = pPeerHTCap->MimoPwrSave;
	if(pHTInfo->PeerMimoPs == MIMO_PS_STATIC)
		pMcsFilter = MCS_FILTER_1SS;
	else
		pMcsFilter = MCS_FILTER_ALL;
	//WB add for MCS8 bug
//	pMcsFilter = MCS_FILTER_1SS;
	ieee->HTHighestOperaRate = HTGetHighestMCSRate(ieee, ieee->dot11HTOperationalRateSet, pMcsFilter);
	ieee->HTCurrentOperaRate = ieee->HTHighestOperaRate;

	//
	// Config current operation mode.
	//
	pHTInfo->CurrentOpMode = pPeerHTInfo->OptMode;



}