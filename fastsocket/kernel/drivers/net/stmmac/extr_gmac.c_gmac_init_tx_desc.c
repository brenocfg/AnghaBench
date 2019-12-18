#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int end_ring; scalar_t__ own; } ;
struct TYPE_4__ {TYPE_1__ etx; } ;
struct dma_desc {TYPE_2__ des01; } ;

/* Variables and functions */

__attribute__((used)) static void gmac_init_tx_desc(struct dma_desc *p, unsigned int ring_size)
{
	int i;

	for (i = 0; i < ring_size; i++) {
		p->des01.etx.own = 0;
		if (i == ring_size - 1)
			p->des01.etx.end_ring = 1;
		p++;
	}

	return;
}