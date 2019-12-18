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
typedef  int /*<<< orphan*/  moduleid_t ;
typedef  int /*<<< orphan*/  geoid_t ;

/* Variables and functions */
 int MODULE_GET_BPOS (int /*<<< orphan*/ ) ; 
 int MODULE_GET_RACK (int /*<<< orphan*/ ) ; 
 scalar_t__ cnode_possible (int) ; 
 int /*<<< orphan*/  cnodeid_get_geoid (int) ; 
 int /*<<< orphan*/  geo_module (int /*<<< orphan*/ ) ; 
 int geo_slab (int /*<<< orphan*/ ) ; 
 int geo_slot (int /*<<< orphan*/ ) ; 
 int num_cnodes ; 
 scalar_t__ sn_hwperf_location_to_bpos (char*,int*,int*,int*,int*) ; 

__attribute__((used)) static int sn_hwperf_geoid_to_cnode(char *location)
{
	int cnode;
	geoid_t geoid;
	moduleid_t module_id;
	int rack, bay, slot, slab;
	int this_rack, this_bay, this_slot, this_slab;

	if (sn_hwperf_location_to_bpos(location, &rack, &bay, &slot, &slab))
		return -1;

	/*
	 * FIXME: replace with cleaner for_each_XXX macro which addresses
	 * both compute and IO nodes once ACPI3.0 is available.
	 */
	for (cnode = 0; cnode < num_cnodes; cnode++) {
		geoid = cnodeid_get_geoid(cnode);
		module_id = geo_module(geoid);
		this_rack = MODULE_GET_RACK(module_id);
		this_bay = MODULE_GET_BPOS(module_id);
		this_slot = geo_slot(geoid);
		this_slab = geo_slab(geoid);
		if (rack == this_rack && bay == this_bay &&
			slot == this_slot && slab == this_slab) {
			break;
		}
	}

	return cnode_possible(cnode) ? cnode : -1;
}