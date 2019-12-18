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
struct dm_thin_device {int dummy; } ;
struct dm_pool_metadata {int /*<<< orphan*/  root_lock; int /*<<< orphan*/  fail_io; } ;
typedef  int /*<<< orphan*/  dm_thin_id ;

/* Variables and functions */
 int EINVAL ; 
 int __open_device (struct dm_pool_metadata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_thin_device**) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int dm_pool_open_thin_device(struct dm_pool_metadata *pmd, dm_thin_id dev,
			     struct dm_thin_device **td)
{
	int r = -EINVAL;

	down_write(&pmd->root_lock);
	if (!pmd->fail_io)
		r = __open_device(pmd, dev, 0, td);
	up_write(&pmd->root_lock);

	return r;
}