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
struct efx_tx_queue {size_t read_count; size_t write_count; size_t ptr_mask; struct efx_tx_buffer* buffer; } ;
struct efx_tx_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  efx_dequeue_buffer (struct efx_tx_queue*,struct efx_tx_buffer*) ; 

void efx_release_tx_buffers(struct efx_tx_queue *tx_queue)
{
	struct efx_tx_buffer *buffer;

	if (!tx_queue->buffer)
		return;

	/* Free any buffers left in the ring */
	while (tx_queue->read_count != tx_queue->write_count) {
		buffer = &tx_queue->buffer[tx_queue->read_count & tx_queue->ptr_mask];
		efx_dequeue_buffer(tx_queue, buffer);

		++tx_queue->read_count;
	}
}