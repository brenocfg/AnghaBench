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
struct dm_table {int /*<<< orphan*/  mempools; int /*<<< orphan*/  integrity_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*) ; 
 unsigned int DM_TYPE_NONE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dm_alloc_md_mempools (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int dm_table_get_type (struct dm_table*) ; 
 scalar_t__ unlikely (int) ; 

int dm_table_alloc_md_mempools(struct dm_table *t)
{
	unsigned type = dm_table_get_type(t);

	if (unlikely(type == DM_TYPE_NONE)) {
		DMWARN("no table type is set, can't allocate mempools");
		return -EINVAL;
	}

	t->mempools = dm_alloc_md_mempools(type, t->integrity_supported);
	if (!t->mempools)
		return -ENOMEM;

	return 0;
}