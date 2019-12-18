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
struct dm_target {int dummy; } ;
struct dm_table {int num_targets; unsigned int num_allocated; struct dm_target* targets; struct dm_target* highs; } ;
typedef  struct dm_target sector_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ dm_vcalloc (unsigned int,int) ; 
 int /*<<< orphan*/  memcpy (struct dm_target*,struct dm_target*,int) ; 
 int /*<<< orphan*/  memset (struct dm_target*,int,int) ; 
 int /*<<< orphan*/  vfree (struct dm_target*) ; 

__attribute__((used)) static int alloc_targets(struct dm_table *t, unsigned int num)
{
	sector_t *n_highs;
	struct dm_target *n_targets;
	int n = t->num_targets;

	/*
	 * Allocate both the target array and offset array at once.
	 * Append an empty entry to catch sectors beyond the end of
	 * the device.
	 */
	n_highs = (sector_t *) dm_vcalloc(num + 1, sizeof(struct dm_target) +
					  sizeof(sector_t));
	if (!n_highs)
		return -ENOMEM;

	n_targets = (struct dm_target *) (n_highs + num);

	if (n) {
		memcpy(n_highs, t->highs, sizeof(*n_highs) * n);
		memcpy(n_targets, t->targets, sizeof(*n_targets) * n);
	}

	memset(n_highs + n, -1, sizeof(*n_highs) * (num - n));
	vfree(t->highs);

	t->num_allocated = num;
	t->highs = n_highs;
	t->targets = n_targets;

	return 0;
}