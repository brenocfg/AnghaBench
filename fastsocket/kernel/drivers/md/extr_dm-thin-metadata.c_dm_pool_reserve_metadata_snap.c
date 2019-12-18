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
struct dm_pool_metadata {int /*<<< orphan*/  root_lock; int /*<<< orphan*/  fail_io; } ;

/* Variables and functions */
 int EINVAL ; 
 int __reserve_metadata_snap (struct dm_pool_metadata*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int dm_pool_reserve_metadata_snap(struct dm_pool_metadata *pmd)
{
	int r = -EINVAL;

	down_write(&pmd->root_lock);
	if (!pmd->fail_io)
		r = __reserve_metadata_snap(pmd);
	up_write(&pmd->root_lock);

	return r;
}