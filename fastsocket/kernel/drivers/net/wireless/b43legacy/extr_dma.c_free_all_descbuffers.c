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
struct b43legacy_dmaring {int nr_slots; int /*<<< orphan*/  rx_buffersize; scalar_t__ tx; int /*<<< orphan*/  used_slots; } ;
struct b43legacy_dmadesc_meta {int /*<<< orphan*/  dmaaddr; TYPE_1__* skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  free_descriptor_buffer (struct b43legacy_dmaring*,struct b43legacy_dmadesc_meta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op32_idx2desc (struct b43legacy_dmaring*,int,struct b43legacy_dmadesc_meta**) ; 
 int /*<<< orphan*/  unmap_descbuffer (struct b43legacy_dmaring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void free_all_descbuffers(struct b43legacy_dmaring *ring)
{
	struct b43legacy_dmadesc_meta *meta;
	int i;

	if (!ring->used_slots)
		return;
	for (i = 0; i < ring->nr_slots; i++) {
		op32_idx2desc(ring, i, &meta);

		if (!meta->skb) {
			B43legacy_WARN_ON(!ring->tx);
			continue;
		}
		if (ring->tx)
			unmap_descbuffer(ring, meta->dmaaddr,
					 meta->skb->len, 1);
		else
			unmap_descbuffer(ring, meta->dmaaddr,
					 ring->rx_buffersize, 0);
		free_descriptor_buffer(ring, meta, 0);
	}
}