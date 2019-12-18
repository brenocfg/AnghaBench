#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  bforced_tx20Mhz; } ;
struct ieee80211_device {TYPE_1__ bandwidth_auto_switch; TYPE_3__* pHTInfo; } ;
struct TYPE_6__ {int bPacketBW; int data_rate; scalar_t__ bBroadcast; scalar_t__ bMulticast; } ;
typedef  TYPE_2__ cb_desc ;
struct TYPE_7__ {scalar_t__ bCurTxBW40MHz; scalar_t__ bCurBW40MHz; int /*<<< orphan*/  bEnableHT; int /*<<< orphan*/  bCurrentHTSupport; } ;
typedef  TYPE_3__* PRT_HIGH_THROUGHPUT ;

/* Variables and functions */

void ieee80211_query_BandwidthMode(struct ieee80211_device* ieee, cb_desc *tcb_desc)
{
	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;

	tcb_desc->bPacketBW = false;

	if(!pHTInfo->bCurrentHTSupport||!pHTInfo->bEnableHT)
		return;

	if(tcb_desc->bMulticast || tcb_desc->bBroadcast)
		return;

	if((tcb_desc->data_rate & 0x80)==0) // If using legacy rate, it shall use 20MHz channel.
		return;
	//BandWidthAutoSwitch is for auto switch to 20 or 40 in long distance
	if(pHTInfo->bCurBW40MHz && pHTInfo->bCurTxBW40MHz && !ieee->bandwidth_auto_switch.bforced_tx20Mhz)
		tcb_desc->bPacketBW = true;
	return;
}