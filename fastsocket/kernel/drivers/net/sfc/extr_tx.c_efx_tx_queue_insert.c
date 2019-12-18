#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct efx_tx_queue {unsigned int insert_count; unsigned int ptr_mask; scalar_t__ read_count; struct efx_tx_buffer* buffer; struct efx_nic* efx; } ;
struct efx_tx_buffer {int len; int unmap_len; int flags; unsigned int dma_addr; } ;
struct efx_nic {scalar_t__ txq_entries; } ;
typedef  unsigned int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_BUG_ON_PARANOID (int) ; 
 int EFX_TX_BUF_CONT ; 
 unsigned int efx_max_tx_len (struct efx_nic*,unsigned int) ; 

__attribute__((used)) static void efx_tx_queue_insert(struct efx_tx_queue *tx_queue,
				dma_addr_t dma_addr, unsigned len,
				struct efx_tx_buffer **final_buffer)
{
	struct efx_tx_buffer *buffer;
	struct efx_nic *efx = tx_queue->efx;
	unsigned dma_len, insert_ptr;

	EFX_BUG_ON_PARANOID(len <= 0);

	while (1) {
		insert_ptr = tx_queue->insert_count & tx_queue->ptr_mask;
		buffer = &tx_queue->buffer[insert_ptr];
		++tx_queue->insert_count;

		EFX_BUG_ON_PARANOID(tx_queue->insert_count -
				    tx_queue->read_count >=
				    efx->txq_entries);

		EFX_BUG_ON_PARANOID(buffer->len);
		EFX_BUG_ON_PARANOID(buffer->unmap_len);
		EFX_BUG_ON_PARANOID(buffer->flags);

		buffer->dma_addr = dma_addr;

		dma_len = efx_max_tx_len(efx, dma_addr);

		/* If there is enough space to send then do so */
		if (dma_len >= len)
			break;

		buffer->len = dma_len;
		buffer->flags = EFX_TX_BUF_CONT;
		dma_addr += dma_len;
		len -= dma_len;
	}

	EFX_BUG_ON_PARANOID(!len);
	buffer->len = len;
	*final_buffer = buffer;
}