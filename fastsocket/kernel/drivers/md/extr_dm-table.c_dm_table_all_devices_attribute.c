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
struct dm_target {TYPE_1__* type; } ;
struct dm_table {int dummy; } ;
typedef  int /*<<< orphan*/  iterate_devices_callout_fn ;
struct TYPE_2__ {int /*<<< orphan*/  (* iterate_devices ) (struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 unsigned int dm_table_get_num_targets (struct dm_table*) ; 
 struct dm_target* dm_table_get_target (struct dm_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool dm_table_all_devices_attribute(struct dm_table *t,
					   iterate_devices_callout_fn func)
{
	struct dm_target *ti;
	unsigned i = 0;

	while (i < dm_table_get_num_targets(t)) {
		ti = dm_table_get_target(t, i++);

		if (!ti->type->iterate_devices ||
		    !ti->type->iterate_devices(ti, func, NULL))
			return 0;
	}

	return 1;
}