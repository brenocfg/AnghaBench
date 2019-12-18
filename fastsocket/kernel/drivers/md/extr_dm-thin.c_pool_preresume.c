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
struct pool_c {struct pool* pool; } ;
struct pool {int dummy; } ;
struct dm_target {struct pool_c* private; } ;

/* Variables and functions */
 int bind_control_target (struct pool*,struct dm_target*) ; 
 int /*<<< orphan*/  commit (struct pool*) ; 
 int maybe_resize_data_dev (struct dm_target*,int*) ; 
 int maybe_resize_metadata_dev (struct dm_target*,int*) ; 

__attribute__((used)) static int pool_preresume(struct dm_target *ti)
{
	int r;
	bool need_commit1, need_commit2;
	struct pool_c *pt = ti->private;
	struct pool *pool = pt->pool;

	/*
	 * Take control of the pool object.
	 */
	r = bind_control_target(pool, ti);
	if (r)
		return r;

	r = maybe_resize_data_dev(ti, &need_commit1);
	if (r)
		return r;

	r = maybe_resize_metadata_dev(ti, &need_commit2);
	if (r)
		return r;

	if (need_commit1 || need_commit2)
		(void) commit(pool);

	return 0;
}