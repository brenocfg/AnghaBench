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
struct TYPE_2__ {scalar_t__ hdr_addr; int /*<<< orphan*/  pkt_addr; } ;
union ixgbe_adv_rx_desc {TYPE_1__ read; } ;
typedef  size_t u16 ;
struct ixgbe_rx_buffer {scalar_t__ page_offset; scalar_t__ dma; } ;
struct ixgbe_ring {size_t next_to_use; scalar_t__ count; struct ixgbe_rx_buffer* rx_buffer_info; } ;

/* Variables and functions */
 union ixgbe_adv_rx_desc* IXGBE_RX_DESC (struct ixgbe_ring*,size_t) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  ixgbe_alloc_mapped_page (struct ixgbe_ring*,struct ixgbe_rx_buffer*) ; 
 int /*<<< orphan*/  ixgbe_release_rx_desc (struct ixgbe_ring*,size_t) ; 
 scalar_t__ unlikely (int) ; 

void ixgbe_alloc_rx_buffers(struct ixgbe_ring *rx_ring, u16 cleaned_count)
{
	union ixgbe_adv_rx_desc *rx_desc;
	struct ixgbe_rx_buffer *bi;
	u16 i = rx_ring->next_to_use;

	/* nothing to do */
	if (!cleaned_count)
		return;

	rx_desc = IXGBE_RX_DESC(rx_ring, i);
	bi = &rx_ring->rx_buffer_info[i];
	i -= rx_ring->count;

	do {
		if (!ixgbe_alloc_mapped_page(rx_ring, bi))
			break;

		/*
		 * Refresh the desc even if buffer_addrs didn't change
		 * because each write-back erases this info.
		 */
		rx_desc->read.pkt_addr = cpu_to_le64(bi->dma + bi->page_offset);

		rx_desc++;
		bi++;
		i++;
		if (unlikely(!i)) {
			rx_desc = IXGBE_RX_DESC(rx_ring, 0);
			bi = rx_ring->rx_buffer_info;
			i -= rx_ring->count;
		}

		/* clear the hdr_addr for the next_to_use descriptor */
		rx_desc->read.hdr_addr = 0;

		cleaned_count--;
	} while (cleaned_count);

	i += rx_ring->count;

	if (rx_ring->next_to_use != i)
		ixgbe_release_rx_desc(rx_ring, i);
}