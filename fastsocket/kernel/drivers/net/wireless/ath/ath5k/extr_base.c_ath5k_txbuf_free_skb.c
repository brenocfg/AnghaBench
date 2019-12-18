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
struct ath5k_hw {int /*<<< orphan*/  hw; int /*<<< orphan*/  dev; } ;
struct ath5k_buf {TYPE_1__* desc; scalar_t__ skbaddr; TYPE_2__* skb; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct TYPE_3__ {scalar_t__ ds_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ ,TYPE_2__*) ; 

void
ath5k_txbuf_free_skb(struct ath5k_hw *ah, struct ath5k_buf *bf)
{
	BUG_ON(!bf);
	if (!bf->skb)
		return;
	dma_unmap_single(ah->dev, bf->skbaddr, bf->skb->len,
			DMA_TO_DEVICE);
	ieee80211_free_txskb(ah->hw, bf->skb);
	bf->skb = NULL;
	bf->skbaddr = 0;
	bf->desc->ds_data = 0;
}