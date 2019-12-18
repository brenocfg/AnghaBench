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
typedef  int /*<<< orphan*/  uint32_t ;
struct dm_target_spec {int /*<<< orphan*/  next; scalar_t__ length; scalar_t__ sector_start; int /*<<< orphan*/  target_type; } ;
struct dm_table {int dummy; } ;
struct dm_ioctl {unsigned int target_count; int /*<<< orphan*/  data_start; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*) ; 
 int EINVAL ; 
 int dm_table_add_target (struct dm_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int dm_table_complete (struct dm_table*) ; 
 int next_target (struct dm_target_spec*,int /*<<< orphan*/ ,void*,struct dm_target_spec**,char**) ; 

__attribute__((used)) static int populate_table(struct dm_table *table,
			  struct dm_ioctl *param, size_t param_size)
{
	int r;
	unsigned int i = 0;
	struct dm_target_spec *spec = (struct dm_target_spec *) param;
	uint32_t next = param->data_start;
	void *end = (void *) param + param_size;
	char *target_params;

	if (!param->target_count) {
		DMWARN("populate_table: no targets specified");
		return -EINVAL;
	}

	for (i = 0; i < param->target_count; i++) {

		r = next_target(spec, next, end, &spec, &target_params);
		if (r) {
			DMWARN("unable to find target");
			return r;
		}

		r = dm_table_add_target(table, spec->target_type,
					(sector_t) spec->sector_start,
					(sector_t) spec->length,
					target_params);
		if (r) {
			DMWARN("error adding target to table");
			return r;
		}

		next = spec->next;
	}

	return dm_table_complete(table);
}