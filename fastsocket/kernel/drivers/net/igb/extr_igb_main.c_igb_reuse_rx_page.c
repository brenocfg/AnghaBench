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
typedef  size_t u16 ;
struct igb_rx_buffer {int /*<<< orphan*/  page_offset; int /*<<< orphan*/  dma; } ;
struct igb_ring {size_t next_to_alloc; size_t count; int /*<<< orphan*/  dev; struct igb_rx_buffer* rx_buffer_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  IGB_RX_BUFSZ ; 
 int /*<<< orphan*/  dma_sync_single_range_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct igb_rx_buffer*,struct igb_rx_buffer*,int) ; 

__attribute__((used)) static void igb_reuse_rx_page(struct igb_ring *rx_ring,
			      struct igb_rx_buffer *old_buff)
{
	struct igb_rx_buffer *new_buff;
	u16 nta = rx_ring->next_to_alloc;

	new_buff = &rx_ring->rx_buffer_info[nta];

	/* update, and store next to alloc */
	nta++;
	rx_ring->next_to_alloc = (nta < rx_ring->count) ? nta : 0;

	/* transfer page from old buffer to new buffer */
	memcpy(new_buff, old_buff, sizeof(struct igb_rx_buffer));

	/* sync the buffer for use by the device */
	dma_sync_single_range_for_device(rx_ring->dev, old_buff->dma,
					 old_buff->page_offset,
					 IGB_RX_BUFSZ,
					 DMA_FROM_DEVICE);
}