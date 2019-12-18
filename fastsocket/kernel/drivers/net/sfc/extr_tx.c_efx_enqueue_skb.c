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
struct sk_buff {int len; int data_len; int /*<<< orphan*/  data; } ;
struct efx_tx_queue {unsigned int write_count; unsigned int insert_count; unsigned int ptr_mask; struct efx_tx_buffer* buffer; int /*<<< orphan*/  queue; struct efx_nic* efx; } ;
struct efx_tx_buffer {int flags; int len; int unmap_len; unsigned int dma_addr; struct sk_buff* skb; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; TYPE_1__* pci_dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  unsigned int dma_addr_t ;
struct TYPE_4__ {int nr_frags; int /*<<< orphan*/ * frags; scalar_t__ gso_size; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  EFX_BUG_ON_PARANOID (int) ; 
 unsigned short EFX_TX_BUF_CONT ; 
 unsigned short EFX_TX_BUF_MAP_SINGLE ; 
 unsigned short EFX_TX_BUF_SKB ; 
 scalar_t__ EFX_WORKAROUND_15592 (struct efx_nic*) ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 unsigned int dma_map_single (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (struct device*,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_dequeue_buffer (struct efx_tx_queue*,struct efx_tx_buffer*) ; 
 int /*<<< orphan*/  efx_enqueue_skb_tso (struct efx_tx_queue*,struct sk_buff*) ; 
 unsigned int efx_max_tx_len (struct efx_nic*,unsigned int) ; 
 int /*<<< orphan*/  efx_nic_push_buffers (struct efx_tx_queue*) ; 
 int /*<<< orphan*/  efx_tx_maybe_stop_queue (struct efx_tx_queue*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,int) ; 
 unsigned int skb_frag_dma_map (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int skb_frag_size (int /*<<< orphan*/ *) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_pad (struct sk_buff*,unsigned int) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  tx_err ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

netdev_tx_t efx_enqueue_skb(struct efx_tx_queue *tx_queue, struct sk_buff *skb)
{
	struct efx_nic *efx = tx_queue->efx;
	struct device *dma_dev = &efx->pci_dev->dev;
	struct efx_tx_buffer *buffer;
	skb_frag_t *fragment;
	unsigned int len, unmap_len = 0, insert_ptr;
	dma_addr_t dma_addr, unmap_addr = 0;
	unsigned int dma_len;
	unsigned short dma_flags;
	int i = 0;

	EFX_BUG_ON_PARANOID(tx_queue->write_count != tx_queue->insert_count);

	if (skb_shinfo(skb)->gso_size)
		return efx_enqueue_skb_tso(tx_queue, skb);

	/* Get size of the initial fragment */
	len = skb_headlen(skb);

	/* Pad if necessary */
	if (EFX_WORKAROUND_15592(efx) && skb->len <= 32) {
		EFX_BUG_ON_PARANOID(skb->data_len);
		len = 32 + 1;
		if (skb_pad(skb, len - skb->len))
			return NETDEV_TX_OK;
	}

	/* Map for DMA.  Use dma_map_single rather than dma_map_page
	 * since this is more efficient on machines with sparse
	 * memory.
	 */
	dma_flags = EFX_TX_BUF_MAP_SINGLE;
	dma_addr = dma_map_single(dma_dev, skb->data, len, PCI_DMA_TODEVICE);

	/* Process all fragments */
	while (1) {
		if (unlikely(dma_mapping_error(dma_dev, dma_addr)))
			goto dma_err;

		/* Store fields for marking in the per-fragment final
		 * descriptor */
		unmap_len = len;
		unmap_addr = dma_addr;

		/* Add to TX queue, splitting across DMA boundaries */
		do {
			insert_ptr = tx_queue->insert_count & tx_queue->ptr_mask;
			buffer = &tx_queue->buffer[insert_ptr];
			EFX_BUG_ON_PARANOID(buffer->flags);
			EFX_BUG_ON_PARANOID(buffer->len);
			EFX_BUG_ON_PARANOID(buffer->unmap_len);

			dma_len = efx_max_tx_len(efx, dma_addr);
			if (likely(dma_len >= len))
				dma_len = len;

			/* Fill out per descriptor fields */
			buffer->len = dma_len;
			buffer->dma_addr = dma_addr;
			buffer->flags = EFX_TX_BUF_CONT;
			len -= dma_len;
			dma_addr += dma_len;
			++tx_queue->insert_count;
		} while (len);

		/* Transfer ownership of the unmapping to the final buffer */
		buffer->flags = EFX_TX_BUF_CONT | dma_flags;
		buffer->unmap_len = unmap_len;
		unmap_len = 0;

		/* Get address and size of next fragment */
		if (i >= skb_shinfo(skb)->nr_frags)
			break;
		fragment = &skb_shinfo(skb)->frags[i];
		len = skb_frag_size(fragment);
		i++;
		/* Map for DMA */
		dma_flags = 0;
		dma_addr = skb_frag_dma_map(dma_dev, fragment, 0, len,
					    DMA_TO_DEVICE);
	}

	/* Transfer ownership of the skb to the final buffer */
	buffer->skb = skb;
	buffer->flags = EFX_TX_BUF_SKB | dma_flags;

	/* Pass off to hardware */
	efx_nic_push_buffers(tx_queue);

	efx_tx_maybe_stop_queue(tx_queue);

	return NETDEV_TX_OK;

 dma_err:
	netif_err(efx, tx_err, efx->net_dev,
		  " TX queue %d could not map skb with %d bytes %d "
		  "fragments for DMA\n", tx_queue->queue, skb->len,
		  skb_shinfo(skb)->nr_frags + 1);

	/* Mark the packet as transmitted, and free the SKB ourselves */
	dev_kfree_skb_any(skb);

	/* Work backwards until we hit the original insert pointer value */
	while (tx_queue->insert_count != tx_queue->write_count) {
		--tx_queue->insert_count;
		insert_ptr = tx_queue->insert_count & tx_queue->ptr_mask;
		buffer = &tx_queue->buffer[insert_ptr];
		efx_dequeue_buffer(tx_queue, buffer);
	}

	/* Free the fragment we were mid-way through pushing */
	if (unmap_len) {
		if (dma_flags & EFX_TX_BUF_MAP_SINGLE)
			dma_unmap_single(dma_dev, unmap_addr, unmap_len,
					 DMA_TO_DEVICE);
		else
			dma_unmap_page(dma_dev, unmap_addr, unmap_len,
				       DMA_TO_DEVICE);
	}

	return NETDEV_TX_OK;
}