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
struct thin_c {struct pool* pool; } ;
struct pool {int /*<<< orphan*/  pmd; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  PM_OUT_OF_DATA_SPACE ; 
 scalar_t__ PM_WRITE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  check_low_water_mark (struct pool*,int /*<<< orphan*/ ) ; 
 int commit (struct pool*) ; 
 int dm_pool_alloc_data_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dm_pool_get_free_block_count (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ get_pool_mode (struct pool*) ; 
 int /*<<< orphan*/  metadata_operation_failed (struct pool*,char*,int) ; 
 int /*<<< orphan*/  set_pool_mode (struct pool*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_data_block(struct thin_c *tc, dm_block_t *result)
{
	int r;
	dm_block_t free_blocks;
	struct pool *pool = tc->pool;

	if (WARN_ON(get_pool_mode(pool) != PM_WRITE))
		return -EINVAL;

	r = dm_pool_get_free_block_count(pool->pmd, &free_blocks);
	if (r) {
		metadata_operation_failed(pool, "dm_pool_get_free_block_count", r);
		return r;
	}

	check_low_water_mark(pool, free_blocks);

	if (!free_blocks) {
		/*
		 * Try to commit to see if that will free up some
		 * more space.
		 */
		r = commit(pool);
		if (r)
			return r;

		r = dm_pool_get_free_block_count(pool->pmd, &free_blocks);
		if (r) {
			metadata_operation_failed(pool, "dm_pool_get_free_block_count", r);
			return r;
		}

		if (!free_blocks) {
			set_pool_mode(pool, PM_OUT_OF_DATA_SPACE);
			return -ENOSPC;
		}
	}

	r = dm_pool_alloc_data_block(pool->pmd, result);
	if (r) {
		metadata_operation_failed(pool, "dm_pool_alloc_data_block", r);
		return r;
	}

	return 0;
}