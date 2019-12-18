#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  zcb_checkpoint_size; int /*<<< orphan*/  zcb_vd_obsolete_counts; TYPE_5__* zcb_spa; } ;
typedef  TYPE_3__ zdb_cb_t ;
struct TYPE_24__ {int vdev_children; } ;
typedef  TYPE_4__ vdev_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_25__ {TYPE_2__* spa_log_class; TYPE_1__* spa_normal_class; TYPE_4__* spa_root_vdev; TYPE_6__* spa_dsl_pool; } ;
typedef  TYPE_5__ spa_t ;
struct TYPE_26__ {int /*<<< orphan*/  dp_obsolete_bpobj; } ;
typedef  TYPE_6__ dsl_pool_t ;
struct TYPE_22__ {int /*<<< orphan*/ * mc_ops; } ;
struct TYPE_21__ {int /*<<< orphan*/ * mc_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_CONFIG ; 
 int /*<<< orphan*/  SM_ALLOC ; 
 int /*<<< orphan*/  SPA_FEATURE_DEVICE_REMOVAL ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 scalar_t__ bpobj_is_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpobj_iterate_nofree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dump_opt ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  increment_indirect_mapping_cb ; 
 int /*<<< orphan*/  load_concrete_ms_allocatable_trees (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_is_enabled (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_get_checkpoint_space (TYPE_5__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  umem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zdb_ddt_leak_init (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  zdb_leak_init_exclude_checkpoint (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  zdb_leak_init_prepare_indirect_vdevs (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  zdb_metaslab_ops ; 

__attribute__((used)) static void
zdb_leak_init(spa_t *spa, zdb_cb_t *zcb)
{
	zcb->zcb_spa = spa;

	if (!dump_opt['L']) {
		dsl_pool_t *dp = spa->spa_dsl_pool;
		vdev_t *rvd = spa->spa_root_vdev;

		/*
		 * We are going to be changing the meaning of the metaslab's
		 * ms_allocatable.  Ensure that the allocator doesn't try to
		 * use the tree.
		 */
		spa->spa_normal_class->mc_ops = &zdb_metaslab_ops;
		spa->spa_log_class->mc_ops = &zdb_metaslab_ops;

		zcb->zcb_vd_obsolete_counts =
		    umem_zalloc(rvd->vdev_children * sizeof (uint32_t *),
		    UMEM_NOFAIL);

		/*
		 * For leak detection, we overload the ms_allocatable trees
		 * to contain allocated segments instead of free segments.
		 * As a result, we can't use the normal metaslab_load/unload
		 * interfaces.
		 */
		zdb_leak_init_prepare_indirect_vdevs(spa, zcb);
		load_concrete_ms_allocatable_trees(spa, SM_ALLOC);

		/*
		 * On load_concrete_ms_allocatable_trees() we loaded all the
		 * allocated entries from the ms_sm to the ms_allocatable for
		 * each metaslab. If the pool has a checkpoint or is in the
		 * middle of discarding a checkpoint, some of these blocks
		 * may have been freed but their ms_sm may not have been
		 * updated because they are referenced by the checkpoint. In
		 * order to avoid false-positives during leak-detection, we
		 * go through the vdev's checkpoint space map and exclude all
		 * its entries from their relevant ms_allocatable.
		 *
		 * We also aggregate the space held by the checkpoint and add
		 * it to zcb_checkpoint_size.
		 *
		 * Note that at this point we are also verifying that all the
		 * entries on the checkpoint_sm are marked as allocated in
		 * the ms_sm of their relevant metaslab.
		 * [see comment in checkpoint_sm_exclude_entry_cb()]
		 */
		zdb_leak_init_exclude_checkpoint(spa, zcb);

		/* for cleaner progress output */
		(void) fprintf(stderr, "\n");

		if (bpobj_is_open(&dp->dp_obsolete_bpobj)) {
			ASSERT(spa_feature_is_enabled(spa,
			    SPA_FEATURE_DEVICE_REMOVAL));
			(void) bpobj_iterate_nofree(&dp->dp_obsolete_bpobj,
			    increment_indirect_mapping_cb, zcb, NULL);
		}
	} else {
		/*
		 * If leak tracing is disabled, we still need to consider
		 * any checkpointed space in our space verification.
		 */
		zcb->zcb_checkpoint_size += spa_get_checkpoint_space(spa);
	}

	spa_config_enter(spa, SCL_CONFIG, FTAG, RW_READER);
	zdb_ddt_leak_init(spa, zcb);
	spa_config_exit(spa, SCL_CONFIG, FTAG);
}