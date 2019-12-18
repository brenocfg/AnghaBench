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
struct b43_dmaring {TYPE_1__* ops; int /*<<< orphan*/  tx; } ;
struct TYPE_2__ {int (* get_current_rxslot ) (struct b43_dmaring*) ;int /*<<< orphan*/  (* set_current_rxslot ) (struct b43_dmaring*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  B43_WARN_ON (int /*<<< orphan*/ ) ; 
 int prev_slot (struct b43_dmaring*,int) ; 
 int stub1 (struct b43_dmaring*) ; 
 int /*<<< orphan*/  stub2 (struct b43_dmaring*,int) ; 

void b43_dma_handle_rx_overflow(struct b43_dmaring *ring)
{
	int current_slot, previous_slot;

	B43_WARN_ON(ring->tx);

	/* Device has filled all buffers, drop all packets and let TCP
	 * decrease speed.
	 * Decrement RX index by one will let the device to see all slots
	 * as free again
	 */
	/*
	*TODO: How to increase rx_drop in mac80211?
	*/
	current_slot = ring->ops->get_current_rxslot(ring);
	previous_slot = prev_slot(ring, current_slot);
	ring->ops->set_current_rxslot(ring, previous_slot);
}