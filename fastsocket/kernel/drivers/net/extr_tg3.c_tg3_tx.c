#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  size_t u32 ;
struct tg3_tx_ring_info {int fragmented; struct sk_buff* skb; } ;
struct tg3_napi {size_t tx_cons; struct tg3_tx_ring_info* tx_buffers; TYPE_3__* tx_ring; TYPE_2__* hw_status; struct tg3* tp; } ;
struct tg3 {int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; struct tg3_napi* napi; } ;
struct skb_shared_hwtstamps {int dummy; } ;
struct sk_buff {int dummy; } ;
struct netdev_queue {int dummy; } ;
struct TYPE_8__ {int nr_frags; int /*<<< orphan*/ * frags; } ;
struct TYPE_7__ {int len_flags; } ;
struct TYPE_6__ {TYPE_1__* idx; } ;
struct TYPE_5__ {size_t tx_consumer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_TSS ; 
 size_t NEXT_TX (size_t) ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  TG3_TX_TSTAMP_LSB ; 
 int /*<<< orphan*/  TG3_TX_TSTAMP_MSB ; 
 scalar_t__ TG3_TX_WAKEUP_THRESH (struct tg3_napi*) ; 
 int TXD_FLAG_HWTSTAMP ; 
 int /*<<< orphan*/  __netif_tx_lock (struct netdev_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __netif_tx_unlock (struct netdev_queue*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct tg3_tx_ring_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping ; 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,int) ; 
 scalar_t__ netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tstamp_tx (struct sk_buff*,struct skb_shared_hwtstamps*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_hwclock_to_timestamp (struct tg3*,int,struct skb_shared_hwtstamps*) ; 
 scalar_t__ tg3_tx_avail (struct tg3_napi*) ; 
 int /*<<< orphan*/  tg3_tx_recover (struct tg3*) ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void tg3_tx(struct tg3_napi *tnapi)
{
	struct tg3 *tp = tnapi->tp;
	u32 hw_idx = tnapi->hw_status->idx[0].tx_consumer;
	u32 sw_idx = tnapi->tx_cons;
	struct netdev_queue *txq;
	int index = tnapi - tp->napi;

	if (tg3_flag(tp, ENABLE_TSS))
		index--;

	txq = netdev_get_tx_queue(tp->dev, index);

	while (sw_idx != hw_idx) {
		struct tg3_tx_ring_info *ri = &tnapi->tx_buffers[sw_idx];
		struct sk_buff *skb = ri->skb;
		int i, tx_bug = 0;

		if (unlikely(skb == NULL)) {
			tg3_tx_recover(tp);
			return;
		}

		if (tnapi->tx_ring[sw_idx].len_flags & TXD_FLAG_HWTSTAMP) {
			struct skb_shared_hwtstamps timestamp;
			u64 hwclock = tr32(TG3_TX_TSTAMP_LSB);
			hwclock |= (u64)tr32(TG3_TX_TSTAMP_MSB) << 32;

			tg3_hwclock_to_timestamp(tp, hwclock, &timestamp);

			skb_tstamp_tx(skb, &timestamp);
		}

		pci_unmap_single(tp->pdev,
				 dma_unmap_addr(ri, mapping),
				 skb_headlen(skb),
				 PCI_DMA_TODEVICE);

		ri->skb = NULL;

		while (ri->fragmented) {
			ri->fragmented = false;
			sw_idx = NEXT_TX(sw_idx);
			ri = &tnapi->tx_buffers[sw_idx];
		}

		sw_idx = NEXT_TX(sw_idx);

		for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
			ri = &tnapi->tx_buffers[sw_idx];
			if (unlikely(ri->skb != NULL || sw_idx == hw_idx))
				tx_bug = 1;

			pci_unmap_page(tp->pdev,
				       dma_unmap_addr(ri, mapping),
				       skb_frag_size(&skb_shinfo(skb)->frags[i]),
				       PCI_DMA_TODEVICE);

			while (ri->fragmented) {
				ri->fragmented = false;
				sw_idx = NEXT_TX(sw_idx);
				ri = &tnapi->tx_buffers[sw_idx];
			}

			sw_idx = NEXT_TX(sw_idx);
		}

		dev_kfree_skb(skb);

		if (unlikely(tx_bug)) {
			tg3_tx_recover(tp);
			return;
		}
	}

	tnapi->tx_cons = sw_idx;

	/* Need to make the tx_cons update visible to tg3_start_xmit()
	 * before checking for netif_queue_stopped().  Without the
	 * memory barrier, there is a small possibility that tg3_start_xmit()
	 * will miss it and cause the queue to be stopped forever.
	 */
	smp_mb();

	if (unlikely(netif_tx_queue_stopped(txq) &&
		     (tg3_tx_avail(tnapi) > TG3_TX_WAKEUP_THRESH(tnapi)))) {
		__netif_tx_lock(txq, smp_processor_id());
		if (netif_tx_queue_stopped(txq) &&
		    (tg3_tx_avail(tnapi) > TG3_TX_WAKEUP_THRESH(tnapi)))
			netif_tx_wake_queue(txq);
		__netif_tx_unlock(txq);
	}
}