#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  mzi_collectable; } ;
typedef  TYPE_1__ mach_zone_info_t ;

/* Variables and functions */
 scalar_t__ GET_MZI_COLLECTABLE_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all_zones_lock ; 
 scalar_t__ get_zone_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ num_zones ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zone_array ; 

uint64_t
get_zones_collectable_bytes(void)
{
	unsigned int i, max_zones;
	uint64_t zones_collectable_bytes = 0;
	mach_zone_info_t zi;

	simple_lock(&all_zones_lock);
	max_zones = (unsigned int)(num_zones);
	simple_unlock(&all_zones_lock);

	for (i = 0; i < max_zones; i++) {
		if (get_zone_info(&(zone_array[i]), NULL, &zi)) {
			zones_collectable_bytes += GET_MZI_COLLECTABLE_BYTES(zi.mzi_collectable);
		}
	}

	return zones_collectable_bytes;
}