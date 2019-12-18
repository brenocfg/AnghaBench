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
struct TYPE_3__ {int own; int end_ring; int disable_ic; scalar_t__ buffer1_size; } ;
struct TYPE_4__ {TYPE_1__ rx; } ;
struct dma_desc {TYPE_2__ des01; } ;

/* Variables and functions */
 scalar_t__ BUF_SIZE_2KiB ; 

__attribute__((used)) static void mac100_init_rx_desc(struct dma_desc *p, unsigned int ring_size,
				int disable_rx_ic)
{
	int i;
	for (i = 0; i < ring_size; i++) {
		p->des01.rx.own = 1;
		p->des01.rx.buffer1_size = BUF_SIZE_2KiB - 1;
		if (i == ring_size - 1)
			p->des01.rx.end_ring = 1;
		if (disable_rx_ic)
			p->des01.rx.disable_ic = 1;
		p++;
	}
	return;
}