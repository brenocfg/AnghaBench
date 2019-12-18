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
struct pch_gbe_rx_ring {unsigned int count; unsigned long size; int dma; scalar_t__ next_to_use; scalar_t__ next_to_clean; struct pch_gbe_buffer* desc; struct pch_gbe_buffer* buffer_info; } ;
struct pch_gbe_hw {TYPE_1__* reg; } ;
struct pch_gbe_buffer {int dummy; } ;
struct pch_gbe_adapter {struct pch_gbe_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  RX_DSC_SIZE; int /*<<< orphan*/  RX_DSC_HW_P; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct pch_gbe_buffer*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pch_gbe_unmap_and_free_rx_resource (struct pch_gbe_adapter*,struct pch_gbe_buffer*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 

__attribute__((used)) static void
pch_gbe_clean_rx_ring(struct pch_gbe_adapter *adapter,
		      struct pch_gbe_rx_ring *rx_ring)
{
	struct pch_gbe_hw *hw = &adapter->hw;
	struct pch_gbe_buffer *buffer_info;
	unsigned long size;
	unsigned int i;

	/* Free all the Rx ring sk_buffs */
	for (i = 0; i < rx_ring->count; i++) {
		buffer_info = &rx_ring->buffer_info[i];
		pch_gbe_unmap_and_free_rx_resource(adapter, buffer_info);
	}
	pr_debug("call pch_gbe_unmap_and_free_rx_resource() %d count\n", i);
	size = (unsigned long)sizeof(struct pch_gbe_buffer) * rx_ring->count;
	memset(rx_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */
	memset(rx_ring->desc, 0, rx_ring->size);
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
	iowrite32(rx_ring->dma, &hw->reg->RX_DSC_HW_P);
	iowrite32((rx_ring->size - 0x10), &hw->reg->RX_DSC_SIZE);
}