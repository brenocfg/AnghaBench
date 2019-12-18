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
typedef  size_t uint ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct dma_pub {scalar_t__ txavail; } ;
struct brcms_c_info {TYPE_1__* pub; int /*<<< orphan*/  wiphy; TYPE_2__* hw; } ;
struct TYPE_4__ {struct dma_pub** di; } ;
struct TYPE_3__ {int /*<<< orphan*/  ieee_hw; } ;

/* Variables and functions */
 size_t TX_BCMC_FIFO ; 
 scalar_t__ TX_HEADROOM ; 
 int dma_txfast (struct brcms_c_info*,struct dma_pub*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_queue_stopped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_stop_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*) ; 

int
brcms_c_txfifo(struct brcms_c_info *wlc, uint fifo, struct sk_buff *p)
{
	struct dma_pub *dma = wlc->hw->di[fifo];
	int ret;
	u16 queue;

	ret = dma_txfast(wlc, dma, p);
	if (ret	< 0)
		wiphy_err(wlc->wiphy, "txfifo: fatal, toss frames !!!\n");

	/*
	 * Stop queue if DMA ring is full. Reserve some free descriptors,
	 * as we sometimes receive a frame from mac80211 after the queues
	 * are stopped.
	 */
	queue = skb_get_queue_mapping(p);
	if (dma->txavail <= TX_HEADROOM && fifo < TX_BCMC_FIFO &&
	    !ieee80211_queue_stopped(wlc->pub->ieee_hw, queue))
		ieee80211_stop_queue(wlc->pub->ieee_hw, queue);

	return ret;
}