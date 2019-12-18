#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t spa_feature_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_5__ {int /*<<< orphan*/ * ds_feature_inuse; } ;
struct TYPE_4__ {int fi_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DMU_OST_ANY ; 
 int /*<<< orphan*/  FTAG ; 
 size_t SPA_FEATURES ; 
 int ZFEATURE_FLAG_PER_DATASET ; 
 int /*<<< orphan*/  close_objset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dataset_feature_count ; 
 TYPE_2__* dmu_objset_ds (int /*<<< orphan*/ *) ; 
 scalar_t__ dsl_dataset_remap_deadlist_exists (TYPE_2__*) ; 
 int /*<<< orphan*/  dump_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuid_table_destroy () ; 
 int open_objset (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  remap_deadlist_count ; 
 TYPE_1__* spa_feature_table ; 

__attribute__((used)) static int
dump_one_dir(const char *dsname, void *arg)
{
	int error;
	objset_t *os;

	error = open_objset(dsname, DMU_OST_ANY, FTAG, &os);
	if (error != 0)
		return (0);

	for (spa_feature_t f = 0; f < SPA_FEATURES; f++) {
		if (!dmu_objset_ds(os)->ds_feature_inuse[f])
			continue;
		ASSERT(spa_feature_table[f].fi_flags &
		    ZFEATURE_FLAG_PER_DATASET);
		dataset_feature_count[f]++;
	}

	if (dsl_dataset_remap_deadlist_exists(dmu_objset_ds(os))) {
		remap_deadlist_count++;
	}

	dump_dir(os);
	close_objset(os, FTAG);
	fuid_table_destroy();
	return (0);
}