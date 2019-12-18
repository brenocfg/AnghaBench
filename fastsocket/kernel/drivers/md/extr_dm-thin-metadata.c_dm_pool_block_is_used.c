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
typedef  scalar_t__ uint32_t ;
struct dm_pool_metadata {int /*<<< orphan*/  root_lock; int /*<<< orphan*/  data_sm; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int dm_sm_get_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int dm_pool_block_is_used(struct dm_pool_metadata *pmd, dm_block_t b, bool *result)
{
	int r;
	uint32_t ref_count;

	down_read(&pmd->root_lock);
	r = dm_sm_get_count(pmd->data_sm, b, &ref_count);
	if (!r)
		*result = (ref_count != 0);
	up_read(&pmd->root_lock);

	return r;
}