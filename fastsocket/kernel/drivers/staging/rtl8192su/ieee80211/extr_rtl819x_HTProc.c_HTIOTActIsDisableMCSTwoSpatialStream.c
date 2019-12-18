#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_device {int /*<<< orphan*/  dev; scalar_t__ (* is_ap_in_wep_tkip ) (int /*<<< orphan*/ ) ;TYPE_1__* pHTInfo; } ;
struct TYPE_2__ {scalar_t__ IOTPeer; } ;
typedef  TYPE_1__* PRT_HIGH_THROUGHPUT ;

/* Variables and functions */
 int /*<<< orphan*/  Adapter ; 
 int /*<<< orphan*/  BELKINF5D8233V1_RALINK ; 
 int /*<<< orphan*/  EDIMAX_RALINK ; 
 scalar_t__ HT_IOT_PEER_ATHEROS ; 
 scalar_t__ HT_IOT_PEER_MARVELL ; 
 scalar_t__ HT_IOT_PEER_UNKNOWN ; 
 scalar_t__ IS_UNDER_11N_AES_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_RALINK ; 
 int /*<<< orphan*/  PeerMacAddr ; 
 scalar_t__ PlatformCompareMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

bool HTIOTActIsDisableMCSTwoSpatialStream(struct ieee80211_device* ieee)
{
	bool retValue = false;
#ifdef TODO
	// Apply for 819u only
//#if (HAL_CODE_BASE==RTL8192)

	//This rule only apply to Belkin(Ralink) AP
	if(IS_UNDER_11N_AES_MODE(Adapter))
	{
		if((PlatformCompareMemory(PeerMacAddr, BELKINF5D8233V1_RALINK, 3)==0) ||
				(PlatformCompareMemory(PeerMacAddr, PCI_RALINK, 3)==0) ||
				(PlatformCompareMemory(PeerMacAddr, EDIMAX_RALINK, 3)==0))
		{
			//Set True to disable this function. Disable by default, Emily, 2008.04.23
			retValue = false;
		}
	}

//#endif
#endif
#if 1
       PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;
	if(ieee->is_ap_in_wep_tkip && ieee->is_ap_in_wep_tkip(ieee->dev))
	{
		if( (pHTInfo->IOTPeer != HT_IOT_PEER_ATHEROS) &&
		    (pHTInfo->IOTPeer != HT_IOT_PEER_UNKNOWN) &&
		    (pHTInfo->IOTPeer != HT_IOT_PEER_MARVELL) )
			retValue = true;
	}
#endif
	return retValue;
}