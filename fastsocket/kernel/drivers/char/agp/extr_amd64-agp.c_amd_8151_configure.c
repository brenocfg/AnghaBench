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
struct TYPE_4__ {int /*<<< orphan*/  gart_bus_addr; int /*<<< orphan*/  gatt_table_real; } ;
struct TYPE_3__ {int /*<<< orphan*/  misc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_NB_GART ; 
 TYPE_2__* agp_bridge ; 
 int /*<<< orphan*/  amd64_configure (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  amd_flush_garts () ; 
 int /*<<< orphan*/  amd_nb_has_feature (int /*<<< orphan*/ ) ; 
 int amd_nb_num () ; 
 TYPE_1__* node_to_amd_nb (int) ; 
 unsigned long virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amd_8151_configure(void)
{
	unsigned long gatt_bus = virt_to_phys(agp_bridge->gatt_table_real);
	int i;

	if (!amd_nb_has_feature(AMD_NB_GART))
		return 0;

	/* Configure AGP regs in each x86-64 host bridge. */
	for (i = 0; i < amd_nb_num(); i++) {
		agp_bridge->gart_bus_addr =
			amd64_configure(node_to_amd_nb(i)->misc, gatt_bus);
	}
	amd_flush_garts();
	return 0;
}