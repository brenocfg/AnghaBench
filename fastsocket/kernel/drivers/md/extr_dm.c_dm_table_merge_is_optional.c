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
struct TYPE_2__ {scalar_t__ (* iterate_devices ) (struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dm_device_merge_is_compulsory ; 
 unsigned int dm_table_get_num_targets (struct dm_table*) ; 
 struct dm_target* dm_table_get_target (struct dm_table*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dm_table_merge_is_optional(struct dm_table *table)
{
	unsigned i = 0;
	struct dm_target *ti;

	while (i < dm_table_get_num_targets(table)) {
		ti = dm_table_get_target(table, i++);

		if (ti->type->iterate_devices &&
		    ti->type->iterate_devices(ti, dm_device_merge_is_compulsory, NULL))
			return 0;
	}

	return 1;
}