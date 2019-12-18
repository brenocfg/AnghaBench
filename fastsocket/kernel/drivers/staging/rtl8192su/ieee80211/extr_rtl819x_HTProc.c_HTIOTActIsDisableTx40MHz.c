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
struct TYPE_3__ {scalar_t__ bdSupportHT; } ;
struct ieee80211_network {TYPE_1__ bssht; } ;
struct ieee80211_device {scalar_t__ pairwise_key_type; scalar_t__ group_key_type; TYPE_2__* pHTInfo; } ;
struct TYPE_4__ {scalar_t__ IOTPeer; } ;
typedef  TYPE_2__* PRT_HIGH_THROUGHPUT ;

/* Variables and functions */
 scalar_t__ HT_IOT_PEER_REALTEK ; 
 scalar_t__ KEY_TYPE_TKIP ; 
 scalar_t__ KEY_TYPE_WEP104 ; 
 scalar_t__ KEY_TYPE_WEP40 ; 

u8
HTIOTActIsDisableTx40MHz(struct ieee80211_device* ieee,struct ieee80211_network *network)
{
	u8	retValue = 0;

	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;
	if(	(KEY_TYPE_WEP104 == ieee->pairwise_key_type) ||
		(KEY_TYPE_WEP40 == ieee->pairwise_key_type) ||
		(KEY_TYPE_WEP104 == ieee->group_key_type) ||
		(KEY_TYPE_WEP40 == ieee->group_key_type) ||
		(KEY_TYPE_TKIP == ieee->pairwise_key_type) )
	{
		if((pHTInfo->IOTPeer==HT_IOT_PEER_REALTEK) && (network->bssht.bdSupportHT))
			retValue = 1;
	}

	return retValue;
}