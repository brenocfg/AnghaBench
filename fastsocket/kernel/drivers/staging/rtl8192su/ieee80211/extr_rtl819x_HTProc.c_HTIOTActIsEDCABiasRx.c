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
typedef  int u8 ;
struct ieee80211_network {int dummy; } ;
struct ieee80211_device {TYPE_1__* pHTInfo; } ;
struct TYPE_2__ {scalar_t__ IOTPeer; } ;
typedef  TYPE_1__* PRT_HIGH_THROUGHPUT ;

/* Variables and functions */
 scalar_t__ HT_IOT_PEER_ATHEROS ; 
 scalar_t__ HT_IOT_PEER_BROADCOM ; 
 scalar_t__ HT_IOT_PEER_RALINK ; 

u8
  HTIOTActIsEDCABiasRx(struct ieee80211_device* ieee,struct ieee80211_network *network)
{
	u8	retValue = 0;
	//if(IS_HARDWARE_TYPE_8192SU(Adapter))
	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;
	{
//#if UNDER_VISTA
//		if(pBssDesc->Vender==HT_IOT_PEER_ATHEROS ||
//			pBssDesc->Vender==HT_IOT_PEER_RALINK)
//#else
		if(pHTInfo->IOTPeer==HT_IOT_PEER_ATHEROS ||
		   pHTInfo->IOTPeer==HT_IOT_PEER_BROADCOM ||
		   pHTInfo->IOTPeer==HT_IOT_PEER_RALINK)
//#endif
			return 1;

	}
	return retValue;
}