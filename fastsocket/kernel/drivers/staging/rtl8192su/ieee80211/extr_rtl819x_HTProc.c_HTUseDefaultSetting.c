#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_device {int /*<<< orphan*/  HTHighestOperaRate; int /*<<< orphan*/  HTCurrentOperaRate; int /*<<< orphan*/  dot11HTOperationalRateSet; int /*<<< orphan*/  Regdot11HTOperationalRateSet; TYPE_2__* pHTInfo; } ;
struct TYPE_9__ {int /*<<< orphan*/  dot11HTOperationalRateSet; int /*<<< orphan*/  dot11OperationalRateSet; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* InitHalRATRTableHandler ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {TYPE_1__ HalFunc; } ;
struct TYPE_7__ {int bCurrentHTSupport; int /*<<< orphan*/  CurrentMPDUDensity; int /*<<< orphan*/  AMPDU_Factor; int /*<<< orphan*/  CurrentAMPDUFactor; int /*<<< orphan*/  bAMPDUEnable; int /*<<< orphan*/  bCurrentAMPDUEnable; int /*<<< orphan*/  nAMSDU_MaxSize; int /*<<< orphan*/  nCurrent_AMSDU_MaxSize; int /*<<< orphan*/  bAMSDU_Support; int /*<<< orphan*/  bCurrent_AMSDU_Support; int /*<<< orphan*/  bRegShortGI40MHz; int /*<<< orphan*/  bCurShortGI40MHz; int /*<<< orphan*/  bRegShortGI20MHz; int /*<<< orphan*/  bCurShortGI20MHz; int /*<<< orphan*/  bRegBW40MHz; int /*<<< orphan*/  bCurBW40MHz; int /*<<< orphan*/  bRegSuppCCK; int /*<<< orphan*/  bCurSuppCCK; scalar_t__ bEnableHT; } ;
typedef  TYPE_2__* PRT_HIGH_THROUGHPUT ;

/* Variables and functions */
 TYPE_3__* Adapter ; 
 int /*<<< orphan*/  HTFilterMCSRate (struct ieee80211_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTGetHighestMCSRate (struct ieee80211_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCS_FILTER_ALL ; 
 TYPE_4__* pMgntInfo ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void HTUseDefaultSetting(struct ieee80211_device* ieee)
{
	PRT_HIGH_THROUGHPUT pHTInfo = ieee->pHTInfo;
//	u8	regBwOpMode;

	if(pHTInfo->bEnableHT)
	{
		pHTInfo->bCurrentHTSupport = true;

		pHTInfo->bCurSuppCCK = pHTInfo->bRegSuppCCK;

		pHTInfo->bCurBW40MHz = pHTInfo->bRegBW40MHz;

		pHTInfo->bCurShortGI20MHz= pHTInfo->bRegShortGI20MHz;

		pHTInfo->bCurShortGI40MHz= pHTInfo->bRegShortGI40MHz;

		pHTInfo->bCurrent_AMSDU_Support = pHTInfo->bAMSDU_Support;

		pHTInfo->nCurrent_AMSDU_MaxSize = pHTInfo->nAMSDU_MaxSize;

		pHTInfo->bCurrentAMPDUEnable = pHTInfo->bAMPDUEnable;

		pHTInfo->CurrentAMPDUFactor = pHTInfo->AMPDU_Factor;

		pHTInfo->CurrentMPDUDensity = pHTInfo->CurrentMPDUDensity;

		// Set BWOpMode register

		//update RATR index0
		HTFilterMCSRate(ieee, ieee->Regdot11HTOperationalRateSet, ieee->dot11HTOperationalRateSet);
	//function below is not implemented at all. WB
#ifdef TODO
		Adapter->HalFunc.InitHalRATRTableHandler( Adapter, &pMgntInfo->dot11OperationalRateSet, pMgntInfo->dot11HTOperationalRateSet);
#endif
		ieee->HTHighestOperaRate = HTGetHighestMCSRate(ieee, ieee->dot11HTOperationalRateSet, MCS_FILTER_ALL);
		ieee->HTCurrentOperaRate = ieee->HTHighestOperaRate;

	}
	else
	{
		pHTInfo->bCurrentHTSupport = false;
	}
	return;
}