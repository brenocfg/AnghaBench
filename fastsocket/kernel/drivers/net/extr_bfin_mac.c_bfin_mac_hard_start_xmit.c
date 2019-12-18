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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_2__ stats; int /*<<< orphan*/  trans_start; } ;
struct TYPE_8__ {int start_addr; int /*<<< orphan*/  config; } ;
struct TYPE_5__ {scalar_t__ status_word; } ;
struct TYPE_7__ {int packet; struct TYPE_7__* next; TYPE_4__ desc_a; TYPE_1__ status; struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAEN ; 
 int DMA_RUN ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  SSYNC () ; 
 int TE ; 
 int /*<<< orphan*/  adjust_tx_list () ; 
 int bfin_read_DMA2_IRQ_STATUS () ; 
 int bfin_read_EMAC_OPMODE () ; 
 int /*<<< orphan*/  bfin_write_DMA2_CONFIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_DMA2_NEXT_DESC_PTR (TYPE_4__*) ; 
 int /*<<< orphan*/  bfin_write_EMAC_OPMODE (int) ; 
 int /*<<< orphan*/  blackfin_dcache_flush_range (int,int) ; 
 TYPE_3__* current_tx_ptr ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int bfin_mac_hard_start_xmit(struct sk_buff *skb,
				struct net_device *dev)
{
	u16 *data;
	u32 data_align = (unsigned long)(skb->data) & 0x3;
	current_tx_ptr->skb = skb;

	if (data_align == 0x2) {
		/* move skb->data to current_tx_ptr payload */
		data = (u16 *)(skb->data) - 1;
				*data = (u16)(skb->len);
		current_tx_ptr->desc_a.start_addr = (u32)data;
		/* this is important! */
		blackfin_dcache_flush_range((u32)data,
				(u32)((u8 *)data + skb->len + 4));
	} else {
		*((u16 *)(current_tx_ptr->packet)) = (u16)(skb->len);
		memcpy((u8 *)(current_tx_ptr->packet + 2), skb->data,
			skb->len);
		current_tx_ptr->desc_a.start_addr =
			(u32)current_tx_ptr->packet;
		if (current_tx_ptr->status.status_word != 0)
			current_tx_ptr->status.status_word = 0;
		blackfin_dcache_flush_range(
			(u32)current_tx_ptr->packet,
			(u32)(current_tx_ptr->packet + skb->len + 2));
	}

	/* make sure the internal data buffers in the core are drained
	 * so that the DMA descriptors are completely written when the
	 * DMA engine goes to fetch them below
	 */
	SSYNC();

	/* enable this packet's dma */
	current_tx_ptr->desc_a.config |= DMAEN;

	/* tx dma is running, just return */
	if (bfin_read_DMA2_IRQ_STATUS() & DMA_RUN)
		goto out;

	/* tx dma is not running */
	bfin_write_DMA2_NEXT_DESC_PTR(&(current_tx_ptr->desc_a));
	/* dma enabled, read from memory, size is 6 */
	bfin_write_DMA2_CONFIG(current_tx_ptr->desc_a.config);
	/* Turn on the EMAC tx */
	bfin_write_EMAC_OPMODE(bfin_read_EMAC_OPMODE() | TE);

out:
	adjust_tx_list();
	current_tx_ptr = current_tx_ptr->next;
	dev->trans_start = jiffies;
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += (skb->len);
	return NETDEV_TX_OK;
}