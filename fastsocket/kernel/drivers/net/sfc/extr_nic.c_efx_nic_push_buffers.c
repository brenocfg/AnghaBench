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
struct efx_tx_queue {unsigned int write_count; unsigned int insert_count; unsigned int ptr_mask; int /*<<< orphan*/  pushes; struct efx_tx_buffer* buffer; } ;
struct efx_tx_buffer {int flags; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  EFX_POPULATE_QWORD_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EFX_TX_BUF_CONT ; 
 int /*<<< orphan*/  FSF_AZ_TX_KER_BUF_ADDR ; 
 int /*<<< orphan*/  FSF_AZ_TX_KER_BUF_REGION ; 
 int /*<<< orphan*/  FSF_AZ_TX_KER_BYTE_COUNT ; 
 int /*<<< orphan*/  FSF_AZ_TX_KER_CONT ; 
 scalar_t__ efx_may_push_tx_desc (struct efx_tx_queue*,unsigned int) ; 
 int /*<<< orphan*/  efx_notify_tx_desc (struct efx_tx_queue*) ; 
 int /*<<< orphan*/  efx_push_tx_desc (struct efx_tx_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * efx_tx_desc (struct efx_tx_queue*,unsigned int) ; 
 int /*<<< orphan*/  wmb () ; 

void efx_nic_push_buffers(struct efx_tx_queue *tx_queue)
{

	struct efx_tx_buffer *buffer;
	efx_qword_t *txd;
	unsigned write_ptr;
	unsigned old_write_count = tx_queue->write_count;

	BUG_ON(tx_queue->write_count == tx_queue->insert_count);

	do {
		write_ptr = tx_queue->write_count & tx_queue->ptr_mask;
		buffer = &tx_queue->buffer[write_ptr];
		txd = efx_tx_desc(tx_queue, write_ptr);
		++tx_queue->write_count;

		/* Create TX descriptor ring entry */
		BUILD_BUG_ON(EFX_TX_BUF_CONT != 1);
		EFX_POPULATE_QWORD_4(*txd,
				     FSF_AZ_TX_KER_CONT,
				     buffer->flags & EFX_TX_BUF_CONT,
				     FSF_AZ_TX_KER_BYTE_COUNT, buffer->len,
				     FSF_AZ_TX_KER_BUF_REGION, 0,
				     FSF_AZ_TX_KER_BUF_ADDR, buffer->dma_addr);
	} while (tx_queue->write_count != tx_queue->insert_count);

	wmb(); /* Ensure descriptors are written before they are fetched */

	if (efx_may_push_tx_desc(tx_queue, old_write_count)) {
		txd = efx_tx_desc(tx_queue,
				  old_write_count & tx_queue->ptr_mask);
		efx_push_tx_desc(tx_queue, txd);
		++tx_queue->pushes;
	} else {
		efx_notify_tx_desc(tx_queue);
	}
}