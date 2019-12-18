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
struct agp_bridge_data {TYPE_2__* driver; } ;
typedef  unsigned long dma_addr_t ;
struct TYPE_4__ {TYPE_1__* masks; } ;
struct TYPE_3__ {unsigned long mask; } ;

/* Variables and functions */

unsigned long agp_generic_mask_memory(struct agp_bridge_data *bridge,
				      dma_addr_t addr, int type)
{
	/* memory type is ignored in the generic routine */
	if (bridge->driver->masks)
		return addr | bridge->driver->masks[0].mask;
	else
		return addr;
}