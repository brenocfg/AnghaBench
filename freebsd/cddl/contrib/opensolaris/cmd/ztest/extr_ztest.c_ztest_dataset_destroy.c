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
struct TYPE_2__ {int zo_verbose; int zo_threads; scalar_t__ zo_datasets; int /*<<< orphan*/  zo_pool; } ;

/* Variables and functions */
 int DS_FIND_CHILDREN ; 
 int DS_FIND_SNAPSHOTS ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  dmu_objset_find (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  ztest_dataset_name (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ztest_dsl_dataset_cleanup (char*,int) ; 
 int /*<<< orphan*/  ztest_objset_destroy_cb ; 
 TYPE_1__ ztest_opts ; 

__attribute__((used)) static void
ztest_dataset_destroy(int d)
{
	char name[ZFS_MAX_DATASET_NAME_LEN];

	ztest_dataset_name(name, ztest_opts.zo_pool, d);

	if (ztest_opts.zo_verbose >= 3)
		(void) printf("Destroying %s to free up space\n", name);

	/*
	 * Cleanup any non-standard clones and snapshots.  In general,
	 * ztest thread t operates on dataset (t % zopt_datasets),
	 * so there may be more than one thing to clean up.
	 */
	for (int t = d; t < ztest_opts.zo_threads;
	    t += ztest_opts.zo_datasets) {
		ztest_dsl_dataset_cleanup(name, t);
	}

	(void) dmu_objset_find(name, ztest_objset_destroy_cb, NULL,
	    DS_FIND_SNAPSHOTS | DS_FIND_CHILDREN);
}