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
struct sk_buff {scalar_t__ len; } ;
struct pch_gbe_tx_ring {unsigned int next_to_clean; int count; int /*<<< orphan*/  tx_lock; struct pch_gbe_buffer* buffer_info; int /*<<< orphan*/  next_to_use; } ;
struct pch_gbe_tx_desc {int gbec_status; int /*<<< orphan*/  dma_status; } ;
struct pch_gbe_buffer {int mapped; struct sk_buff* skb; int /*<<< orphan*/  length; int /*<<< orphan*/  dma; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_restart_count; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  collisions; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_carrier_errors; } ;
struct pch_gbe_adapter {TYPE_2__ stats; int /*<<< orphan*/  netdev; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int DSC_INIT16 ; 
 int PCH_GBE_DESC_UNUSED (struct pch_gbe_tx_ring*) ; 
 int PCH_GBE_TXD_GMAC_STAT_ABT ; 
 int PCH_GBE_TXD_GMAC_STAT_CMPLT ; 
 int PCH_GBE_TXD_GMAC_STAT_CRSER ; 
 int PCH_GBE_TXD_GMAC_STAT_EXCOL ; 
 int PCH_GBE_TXD_GMAC_STAT_MLTCOL ; 
 int PCH_GBE_TXD_GMAC_STAT_SNGCOL ; 
 struct pch_gbe_tx_desc* PCH_GBE_TX_DESC (struct pch_gbe_tx_ring,unsigned int) ; 
 int PCH_GBE_TX_WEIGHT ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool
pch_gbe_clean_tx(struct pch_gbe_adapter *adapter,
		 struct pch_gbe_tx_ring *tx_ring)
{
	struct pch_gbe_tx_desc *tx_desc;
	struct pch_gbe_buffer *buffer_info;
	struct sk_buff *skb;
	unsigned int i;
	unsigned int cleaned_count = 0;
	bool cleaned = false;
	int unused, thresh;

	pr_debug("next_to_clean : %d\n", tx_ring->next_to_clean);

	i = tx_ring->next_to_clean;
	tx_desc = PCH_GBE_TX_DESC(*tx_ring, i);
	pr_debug("gbec_status:0x%04x  dma_status:0x%04x\n",
		 tx_desc->gbec_status, tx_desc->dma_status);

	unused = PCH_GBE_DESC_UNUSED(tx_ring);
	thresh = tx_ring->count - PCH_GBE_TX_WEIGHT;
	if ((tx_desc->gbec_status == DSC_INIT16) && (unused < thresh))
	{  /* current marked clean, tx queue filling up, do extra clean */
		int j, k;
		if (unused < 8) {  /* tx queue nearly full */
			pr_debug("clean_tx: transmit queue warning (%x,%x) unused=%d\n",
				tx_ring->next_to_clean,tx_ring->next_to_use,unused);
		}

		/* current marked clean, scan for more that need cleaning. */
		k = i;
		for (j = 0; j < PCH_GBE_TX_WEIGHT; j++)
		{
			tx_desc = PCH_GBE_TX_DESC(*tx_ring, k);
			if (tx_desc->gbec_status != DSC_INIT16) break; /*found*/
			if (++k >= tx_ring->count) k = 0;  /*increment, wrap*/
		}
		if (j < PCH_GBE_TX_WEIGHT) {
			pr_debug("clean_tx: unused=%d loops=%d found tx_desc[%x,%x:%x].gbec_status=%04x\n",
				unused,j, i,k, tx_ring->next_to_use, tx_desc->gbec_status);
			i = k;  /*found one to clean, usu gbec_status==2000.*/
		}
	}

	while ((tx_desc->gbec_status & DSC_INIT16) == 0x0000) {
		pr_debug("gbec_status:0x%04x\n", tx_desc->gbec_status);
		buffer_info = &tx_ring->buffer_info[i];
		skb = buffer_info->skb;
		cleaned = true;

		if ((tx_desc->gbec_status & PCH_GBE_TXD_GMAC_STAT_ABT)) {
			adapter->stats.tx_aborted_errors++;
			pr_err("Transfer Abort Error\n");
		} else if ((tx_desc->gbec_status & PCH_GBE_TXD_GMAC_STAT_CRSER)
			  ) {
			adapter->stats.tx_carrier_errors++;
			pr_err("Transfer Carrier Sense Error\n");
		} else if ((tx_desc->gbec_status & PCH_GBE_TXD_GMAC_STAT_EXCOL)
			  ) {
			adapter->stats.tx_aborted_errors++;
			pr_err("Transfer Collision Abort Error\n");
		} else if ((tx_desc->gbec_status &
			    (PCH_GBE_TXD_GMAC_STAT_SNGCOL |
			     PCH_GBE_TXD_GMAC_STAT_MLTCOL))) {
			adapter->stats.collisions++;
			adapter->stats.tx_packets++;
			adapter->stats.tx_bytes += skb->len;
			pr_debug("Transfer Collision\n");
		} else if ((tx_desc->gbec_status & PCH_GBE_TXD_GMAC_STAT_CMPLT)
			  ) {
			adapter->stats.tx_packets++;
			adapter->stats.tx_bytes += skb->len;
		}
		if (buffer_info->mapped) {
			pr_debug("unmap buffer_info->dma : %d\n", i);
			dma_unmap_single(&adapter->pdev->dev, buffer_info->dma,
					 buffer_info->length, DMA_TO_DEVICE);
			buffer_info->mapped = false;
		}
		if (buffer_info->skb) {
			pr_debug("trim buffer_info->skb : %d\n", i);
			skb_trim(buffer_info->skb, 0);
		}
		tx_desc->gbec_status = DSC_INIT16;
		if (unlikely(++i == tx_ring->count))
			i = 0;
		tx_desc = PCH_GBE_TX_DESC(*tx_ring, i);

		/* weight of a sort for tx, to avoid endless transmit cleanup */
		if (cleaned_count++ == PCH_GBE_TX_WEIGHT) {
			cleaned = false;
			break;
		}
	}
	pr_debug("called pch_gbe_unmap_and_free_tx_resource() %d count\n",
		 cleaned_count);
	if (cleaned_count > 0)  { /*skip this if nothing cleaned*/
		/* Recover from running out of Tx resources in xmit_frame */
		spin_lock(&tx_ring->tx_lock);
		if (unlikely(cleaned && (netif_queue_stopped(adapter->netdev))))
		{
			netif_wake_queue(adapter->netdev);
			adapter->stats.tx_restart_count++;
			pr_debug("Tx wake queue\n");
		}

		tx_ring->next_to_clean = i;

		pr_debug("next_to_clean : %d\n", tx_ring->next_to_clean);
		spin_unlock(&tx_ring->tx_lock);
	}
	return cleaned;
}