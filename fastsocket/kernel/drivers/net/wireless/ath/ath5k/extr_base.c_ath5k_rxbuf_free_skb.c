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
struct ath_common {int /*<<< orphan*/  rx_bufsize; } ;
struct ath5k_hw {int /*<<< orphan*/  dev; } ;
struct ath5k_buf {TYPE_1__* desc; scalar_t__ skbaddr; int /*<<< orphan*/ * skb; } ;
struct TYPE_2__ {scalar_t__ ds_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 struct ath_common* ath5k_hw_common (struct ath5k_hw*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ath5k_rxbuf_free_skb(struct ath5k_hw *ah, struct ath5k_buf *bf)
{
	struct ath_common *common = ath5k_hw_common(ah);

	BUG_ON(!bf);
	if (!bf->skb)
		return;
	dma_unmap_single(ah->dev, bf->skbaddr, common->rx_bufsize,
			DMA_FROM_DEVICE);
	dev_kfree_skb_any(bf->skb);
	bf->skb = NULL;
	bf->skbaddr = 0;
	bf->desc->ds_data = 0;
}