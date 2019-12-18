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
struct agp_bridge_data {TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* chipset_flush ) (struct agp_bridge_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct agp_bridge_data*) ; 

void agp_flush_chipset(struct agp_bridge_data *bridge)
{
	if (bridge->driver->chipset_flush)
		bridge->driver->chipset_flush(bridge);
}