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
struct ixgbe_tx_buffer {int dummy; } ;
struct ixgbe_ring {size_t count; unsigned long size; scalar_t__ next_to_clean; scalar_t__ next_to_use; struct ixgbe_tx_buffer* desc; struct ixgbe_tx_buffer* tx_buffer_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_unmap_and_free_tx_resource (struct ixgbe_ring*,struct ixgbe_tx_buffer*) ; 
 int /*<<< orphan*/  memset (struct ixgbe_tx_buffer*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void ixgbe_clean_tx_ring(struct ixgbe_ring *tx_ring)
{
	struct ixgbe_tx_buffer *tx_buffer_info;
	unsigned long size;
	u16 i;

	/* ring already cleared, nothing to do */
	if (!tx_ring->tx_buffer_info)
		return;

	/* Free all the Tx ring sk_buffs */
	for (i = 0; i < tx_ring->count; i++) {
		tx_buffer_info = &tx_ring->tx_buffer_info[i];
		ixgbe_unmap_and_free_tx_resource(tx_ring, tx_buffer_info);
	}

	size = sizeof(struct ixgbe_tx_buffer) * tx_ring->count;
	memset(tx_ring->tx_buffer_info, 0, size);

	/* Zero out the descriptor ring */
	memset(tx_ring->desc, 0, tx_ring->size);

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;
}