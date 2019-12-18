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
struct b43legacy_dmaring {int tx; int nr_slots; int current_slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  dma_rx (struct b43legacy_dmaring*,int*) ; 
 int next_slot (struct b43legacy_dmaring*,int) ; 
 int op32_get_current_rxslot (struct b43legacy_dmaring*) ; 
 int /*<<< orphan*/  op32_set_current_rxslot (struct b43legacy_dmaring*,int) ; 
 int /*<<< orphan*/  update_max_used_slots (struct b43legacy_dmaring*,int) ; 

void b43legacy_dma_rx(struct b43legacy_dmaring *ring)
{
	int slot;
	int current_slot;
	int used_slots = 0;

	B43legacy_WARN_ON(ring->tx);
	current_slot = op32_get_current_rxslot(ring);
	B43legacy_WARN_ON(!(current_slot >= 0 && current_slot <
			   ring->nr_slots));

	slot = ring->current_slot;
	for (; slot != current_slot; slot = next_slot(ring, slot)) {
		dma_rx(ring, &slot);
		update_max_used_slots(ring, ++used_slots);
	}
	op32_set_current_rxslot(ring, slot);
	ring->current_slot = slot;
}