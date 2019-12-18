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
struct b43legacy_dmaring {struct b43legacy_dmaring* meta; struct b43legacy_dmaring* txhdr_cache; int /*<<< orphan*/  nr_slots; int /*<<< orphan*/  max_used_slots; scalar_t__ tx; int /*<<< orphan*/  mmio_base; scalar_t__ type; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43legacydbg (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmacontroller_cleanup (struct b43legacy_dmaring*) ; 
 int /*<<< orphan*/  free_all_descbuffers (struct b43legacy_dmaring*) ; 
 int /*<<< orphan*/  free_ringmemory (struct b43legacy_dmaring*) ; 
 int /*<<< orphan*/  kfree (struct b43legacy_dmaring*) ; 

__attribute__((used)) static void b43legacy_destroy_dmaring(struct b43legacy_dmaring *ring)
{
	if (!ring)
		return;

	b43legacydbg(ring->dev->wl, "DMA-%u 0x%04X (%s) max used slots:"
		     " %d/%d\n", (unsigned int)(ring->type), ring->mmio_base,
		     (ring->tx) ? "TX" : "RX", ring->max_used_slots,
		     ring->nr_slots);
	/* Device IRQs are disabled prior entering this function,
	 * so no need to take care of concurrency with rx handler stuff.
	 */
	dmacontroller_cleanup(ring);
	free_all_descbuffers(ring);
	free_ringmemory(ring);

	kfree(ring->txhdr_cache);
	kfree(ring->meta);
	kfree(ring);
}