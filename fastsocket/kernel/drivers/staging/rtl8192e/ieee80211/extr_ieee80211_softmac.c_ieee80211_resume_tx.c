#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int frag; TYPE_3__* txb; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_packets; } ;
struct ieee80211_device {TYPE_2__ tx_pending; TYPE_1__ stats; int /*<<< orphan*/  rate; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* softmac_data_hard_start_xmit ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ queue_stop; } ;
struct TYPE_6__ {int nr_frags; int /*<<< orphan*/ * fragments; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_txb_free (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ieee80211_resume_tx(struct ieee80211_device *ieee)
{
	int i;
	for(i = ieee->tx_pending.frag; i < ieee->tx_pending.txb->nr_frags; i++) {

		if (ieee->queue_stop){
			ieee->tx_pending.frag = i;
			return;
		}else{

			ieee->softmac_data_hard_start_xmit(
				ieee->tx_pending.txb->fragments[i],
				ieee->dev,ieee->rate);
				//(i+1)<ieee->tx_pending.txb->nr_frags);
			ieee->stats.tx_packets++;
		//	ieee->dev->trans_start = jiffies;
		}
	}


	ieee80211_txb_free(ieee->tx_pending.txb);
	ieee->tx_pending.txb = NULL;
}