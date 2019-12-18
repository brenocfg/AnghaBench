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
struct dm_target {TYPE_1__* type; scalar_t__ discards_supported; int /*<<< orphan*/  num_discard_requests; } ;
struct dm_table {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* iterate_devices ) (struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  device_discard_capable ; 
 unsigned int dm_table_get_num_targets (struct dm_table*) ; 
 struct dm_target* dm_table_get_target (struct dm_table*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool dm_table_supports_discards(struct dm_table *t)
{
	struct dm_target *ti;
	unsigned i = 0;

	/*
	 * Unless any target used by the table set discards_supported,
	 * require at least one underlying device to support discards.
	 * t->devices includes internal dm devices such as mirror logs
	 * so we need to use iterate_devices here, which targets
	 * supporting discard selectively must provide.
	 */
	while (i < dm_table_get_num_targets(t)) {
		ti = dm_table_get_target(t, i++);

		if (!ti->num_discard_requests)
			continue;

		if (ti->discards_supported)
			return 1;

		if (ti->type->iterate_devices &&
		    ti->type->iterate_devices(ti, device_discard_capable, NULL))
			return 1;
	}

	return 0;
}