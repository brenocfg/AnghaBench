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
struct agp_bridge_data {int dummy; } ;
struct TYPE_2__ {scalar_t__ gatt_bus_addr; int /*<<< orphan*/ * gatt_table; int /*<<< orphan*/ * gatt_table_real; } ;

/* Variables and functions */
 TYPE_1__* agp_bridge ; 

__attribute__((used)) static int intel_fake_agp_create_gatt_table(struct agp_bridge_data *bridge)
{
	agp_bridge->gatt_table_real = NULL;
	agp_bridge->gatt_table = NULL;
	agp_bridge->gatt_bus_addr = 0;

	return 0;
}