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
typedef  size_t u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * zones; } ;

/* Variables and functions */
 size_t tipc_max_zones ; 
 TYPE_1__ tipc_net ; 
 int /*<<< orphan*/  tipc_zone_remove_as_router (int /*<<< orphan*/ ,size_t) ; 

void tipc_net_remove_as_router(u32 router)
{
	u32 z_num;

	for (z_num = 1; z_num <= tipc_max_zones; z_num++) {
		if (!tipc_net.zones[z_num])
			continue;
		tipc_zone_remove_as_router(tipc_net.zones[z_num], router);
	}
}