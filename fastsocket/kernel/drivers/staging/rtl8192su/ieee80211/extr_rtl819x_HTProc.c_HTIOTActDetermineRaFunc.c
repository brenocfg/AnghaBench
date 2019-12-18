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
struct ieee80211_device {TYPE_1__* pHTInfo; } ;
struct TYPE_2__ {scalar_t__ IOTPeer; int IOTAction; int /*<<< orphan*/  IOTRaFunc; } ;
typedef  TYPE_1__* PRT_HIGH_THROUGHPUT ;

/* Variables and functions */
 int HT_IOT_ACT_AMSDU_ENABLE ; 
 scalar_t__ HT_IOT_PEER_RALINK ; 
 int /*<<< orphan*/  HT_IOT_RAFUNC_DISABLE_ALL ; 
 int /*<<< orphan*/  HT_IOT_RAFUNC_PEER_1R ; 
 int /*<<< orphan*/  HT_IOT_RAFUNC_TX_AMSDU ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

void
HTIOTActDetermineRaFunc(struct ieee80211_device* ieee,	bool	bPeerRx2ss)
{
	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;
	pHTInfo->IOTRaFunc &= HT_IOT_RAFUNC_DISABLE_ALL;

	if(pHTInfo->IOTPeer == HT_IOT_PEER_RALINK && !bPeerRx2ss)
		pHTInfo->IOTRaFunc |= HT_IOT_RAFUNC_PEER_1R;

	if(pHTInfo->IOTAction & HT_IOT_ACT_AMSDU_ENABLE)
		pHTInfo->IOTRaFunc |= HT_IOT_RAFUNC_TX_AMSDU;

	printk("!!!!!!!!!!!!!!!!!!!!!!!!!!!IOTRaFunc = %8.8x\n", pHTInfo->IOTRaFunc);
}