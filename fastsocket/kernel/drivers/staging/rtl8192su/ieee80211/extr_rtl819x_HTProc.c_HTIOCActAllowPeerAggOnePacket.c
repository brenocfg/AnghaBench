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
struct ieee80211_network {int dummy; } ;
struct ieee80211_device {TYPE_1__* pHTInfo; } ;
struct TYPE_2__ {scalar_t__ IOTPeer; } ;
typedef  TYPE_1__* PRT_HIGH_THROUGHPUT ;

/* Variables and functions */
 scalar_t__ HT_IOT_PEER_MARVELL ; 

bool HTIOCActAllowPeerAggOnePacket(struct ieee80211_device* ieee,struct ieee80211_network *network)
{
	bool 	retValue = false;
	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;
	{
		if(pHTInfo->IOTPeer == HT_IOT_PEER_MARVELL)
			return true;

	}
	return retValue;
}