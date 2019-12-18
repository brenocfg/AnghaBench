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
struct TYPE_2__ {int bus_pick_width; int bus_pick_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 TYPE_1__ sossi ; 

__attribute__((used)) static void sossi_set_bits_per_cycle(int bpc)
{
	int bus_pick_count, bus_pick_width;

	/*
	 * We set explicitly the the bus_pick_count as well, although
	 * with remapping/reordering disabled it will be calculated by HW
	 * as (32 / bus_pick_width).
	 */
	switch (bpc) {
	case 8:
		bus_pick_count = 4;
		bus_pick_width = 8;
		break;
	case 16:
		bus_pick_count = 2;
		bus_pick_width = 16;
		break;
	default:
		BUG();
		return;
	}
	sossi.bus_pick_width = bus_pick_width;
	sossi.bus_pick_count = bus_pick_count;
}