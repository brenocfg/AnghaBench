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
typedef  int /*<<< orphan*/  u32 ;
struct tioca_kernel {int /*<<< orphan*/  ca_gfxgart_base; scalar_t__ ca_gfxgart; } ;
struct agp_bridge_data {int /*<<< orphan*/  gatt_bus_addr; int /*<<< orphan*/ * gatt_table_real; int /*<<< orphan*/ * gatt_table; scalar_t__ dev_private_data; } ;

/* Variables and functions */

__attribute__((used)) static int sgi_tioca_create_gatt_table(struct agp_bridge_data *bridge)
{
	struct tioca_kernel *info =
	    (struct tioca_kernel *)bridge->dev_private_data;

	bridge->gatt_table_real = (u32 *) info->ca_gfxgart;
	bridge->gatt_table = bridge->gatt_table_real;
	bridge->gatt_bus_addr = info->ca_gfxgart_base;

	return 0;
}