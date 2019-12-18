#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {unsigned long long vdev_ms_shift; TYPE_5__* vdev_spa; } ;
typedef  TYPE_3__ vdev_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_18__ {int /*<<< orphan*/  sm_shift; TYPE_2__* sm_phys; } ;
typedef  TYPE_4__ space_map_t ;
struct TYPE_19__ {int /*<<< orphan*/  spa_meta_objset; } ;
typedef  TYPE_5__ spa_t ;
struct TYPE_20__ {unsigned long long ms_size; TYPE_4__* ms_sm; scalar_t__ ms_fragmentation; int /*<<< orphan*/  ms_lock; int /*<<< orphan*/  ms_allocatable; scalar_t__ ms_start; scalar_t__ ms_id; TYPE_1__* ms_group; } ;
typedef  TYPE_6__ metaslab_t ;
typedef  int /*<<< orphan*/  freebuf ;
struct TYPE_16__ {int /*<<< orphan*/  smp_histogram; } ;
struct TYPE_15__ {TYPE_3__* mg_vd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  SPACE_MAP_HISTOGRAM_SIZE ; 
 int /*<<< orphan*/  SPA_FEATURE_SPACEMAP_HISTOGRAM ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_histogram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_metaslab_stats (TYPE_6__*) ; 
 int* dump_opt ; 
 int /*<<< orphan*/  dump_spacemap (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  metaslab_load (TYPE_6__*) ; 
 int /*<<< orphan*/  metaslab_unload (TYPE_6__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  range_tree_stat_verify (int /*<<< orphan*/ ) ; 
 scalar_t__ spa_feature_is_active (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ space_map_allocated (TYPE_4__*) ; 
 scalar_t__ space_map_object (TYPE_4__*) ; 
 int /*<<< orphan*/  zdb_nicenum (scalar_t__,char*,int) ; 

__attribute__((used)) static void
dump_metaslab(metaslab_t *msp)
{
	vdev_t *vd = msp->ms_group->mg_vd;
	spa_t *spa = vd->vdev_spa;
	space_map_t *sm = msp->ms_sm;
	char freebuf[32];

	zdb_nicenum(msp->ms_size - space_map_allocated(sm), freebuf,
	    sizeof (freebuf));

	(void) printf(
	    "\tmetaslab %6llu   offset %12llx   spacemap %6llu   free    %5s\n",
	    (u_longlong_t)msp->ms_id, (u_longlong_t)msp->ms_start,
	    (u_longlong_t)space_map_object(sm), freebuf);

	if (dump_opt['m'] > 2 && !dump_opt['L']) {
		mutex_enter(&msp->ms_lock);
		VERIFY0(metaslab_load(msp));
		range_tree_stat_verify(msp->ms_allocatable);
		dump_metaslab_stats(msp);
		metaslab_unload(msp);
		mutex_exit(&msp->ms_lock);
	}

	if (dump_opt['m'] > 1 && sm != NULL &&
	    spa_feature_is_active(spa, SPA_FEATURE_SPACEMAP_HISTOGRAM)) {
		/*
		 * The space map histogram represents free space in chunks
		 * of sm_shift (i.e. bucket 0 refers to 2^sm_shift).
		 */
		(void) printf("\tOn-disk histogram:\t\tfragmentation %llu\n",
		    (u_longlong_t)msp->ms_fragmentation);
		dump_histogram(sm->sm_phys->smp_histogram,
		    SPACE_MAP_HISTOGRAM_SIZE, sm->sm_shift);
	}

	if (dump_opt['d'] > 5 || dump_opt['m'] > 3) {
		ASSERT(msp->ms_size == (1ULL << vd->vdev_ms_shift));

		dump_spacemap(spa->spa_meta_objset, msp->ms_sm);
	}
}