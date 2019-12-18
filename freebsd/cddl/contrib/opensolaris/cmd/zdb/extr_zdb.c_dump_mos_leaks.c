#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_41__   TYPE_9__ ;
typedef  struct TYPE_40__   TYPE_8__ ;
typedef  struct TYPE_39__   TYPE_7__ ;
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_24__ ;
typedef  struct TYPE_32__   TYPE_23__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_19__ ;
typedef  struct TYPE_29__   TYPE_12__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
struct TYPE_39__ {TYPE_6__* vim_phys; } ;
typedef  TYPE_7__ vdev_indirect_mapping_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_37__ {int /*<<< orphan*/  scip_next_mapping_object; int /*<<< orphan*/  scip_prev_obsolete_sm_object; } ;
struct TYPE_36__ {int /*<<< orphan*/  sav_object; } ;
struct TYPE_35__ {int /*<<< orphan*/  sav_object; } ;
struct TYPE_40__ {TYPE_12__** spa_ddt; int /*<<< orphan*/  spa_root_vdev; TYPE_5__ spa_condensing_indirect_phys; TYPE_4__ spa_spares; TYPE_3__ spa_l2cache; int /*<<< orphan*/  spa_deferred_bpobj; TYPE_9__* spa_dsl_pool; int /*<<< orphan*/  spa_all_vdev_zaps; int /*<<< orphan*/  spa_errlog_scrub; int /*<<< orphan*/  spa_errlog_last; int /*<<< orphan*/  spa_history; int /*<<< orphan*/  spa_feat_for_write_obj; int /*<<< orphan*/  spa_feat_for_read_obj; int /*<<< orphan*/  spa_feat_enabled_txg_obj; int /*<<< orphan*/  spa_feat_desc_obj; int /*<<< orphan*/  spa_ddt_stat_object; int /*<<< orphan*/  spa_config_object; int /*<<< orphan*/  spa_pool_props_object; int /*<<< orphan*/ * spa_meta_objset; } ;
typedef  TYPE_8__ spa_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_41__ {int /*<<< orphan*/ * dp_leak_dir; int /*<<< orphan*/ * dp_free_dir; int /*<<< orphan*/ * dp_mos_dir; TYPE_10__* dp_origin_snap; int /*<<< orphan*/  dp_free_bpobj; int /*<<< orphan*/  dp_obsolete_bpobj; int /*<<< orphan*/  dp_empty_bpobj; TYPE_2__* dp_scan; int /*<<< orphan*/  dp_tmp_userrefs_obj; int /*<<< orphan*/  dp_bptree_obj; } ;
typedef  TYPE_9__ dsl_pool_t ;
struct TYPE_27__ {int /*<<< orphan*/  ds_deadlist; } ;
typedef  TYPE_10__ dsl_dataset_t ;
struct TYPE_28__ {int doi_type; } ;
typedef  TYPE_11__ dmu_object_info_t ;
typedef  size_t dmu_object_byteswap_t ;
struct TYPE_29__ {int /*<<< orphan*/ ** ddt_object; } ;
typedef  TYPE_12__ ddt_t ;
struct TYPE_38__ {int /*<<< orphan*/  vimp_counts_object; } ;
struct TYPE_31__ {int /*<<< orphan*/  scn_queue_obj; } ;
struct TYPE_34__ {TYPE_1__ scn_phys; } ;
struct TYPE_33__ {char* ot_name; } ;
struct TYPE_32__ {char* ob_name; } ;
struct TYPE_30__ {int /*<<< orphan*/  ds_next_snap_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ DDT_CLASSES ; 
 scalar_t__ DDT_TYPES ; 
 size_t DMU_OT_BYTESWAP (int) ; 
 int DMU_OT_NEWTYPE ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 scalar_t__ ZIO_CHECKSUM_FUNCTIONS ; 
 int /*<<< orphan*/  bpobj_count_refd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  count_dir_mos_objects (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  count_ds_mos_objects (TYPE_10__*) ; 
 int /*<<< orphan*/  dmu_object_info (int /*<<< orphan*/ *,scalar_t__,TYPE_11__*) ; 
 scalar_t__ dmu_object_next (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_24__* dmu_ot ; 
 TYPE_23__* dmu_ot_byteswap ; 
 int /*<<< orphan*/  dsl_dataset_hold_obj (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_10__**) ; 
 TYPE_19__* dsl_dataset_phys (TYPE_10__*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_enter (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_exit (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_deadlist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mos_leak_vdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mos_leaks_cb ; 
 int /*<<< orphan*/  mos_obj_refd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mos_refd_objs ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ range_tree_contains (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  range_tree_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_tree_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_tree_remove (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  range_tree_vacate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_walk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_indirect_mapping_close (TYPE_7__*) ; 
 TYPE_7__* vdev_indirect_mapping_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dump_mos_leaks(spa_t *spa)
{
	int rv = 0;
	objset_t *mos = spa->spa_meta_objset;
	dsl_pool_t *dp = spa->spa_dsl_pool;

	/* Visit and mark all referenced objects in the MOS */

	mos_obj_refd(DMU_POOL_DIRECTORY_OBJECT);
	mos_obj_refd(spa->spa_pool_props_object);
	mos_obj_refd(spa->spa_config_object);
	mos_obj_refd(spa->spa_ddt_stat_object);
	mos_obj_refd(spa->spa_feat_desc_obj);
	mos_obj_refd(spa->spa_feat_enabled_txg_obj);
	mos_obj_refd(spa->spa_feat_for_read_obj);
	mos_obj_refd(spa->spa_feat_for_write_obj);
	mos_obj_refd(spa->spa_history);
	mos_obj_refd(spa->spa_errlog_last);
	mos_obj_refd(spa->spa_errlog_scrub);
	mos_obj_refd(spa->spa_all_vdev_zaps);
	mos_obj_refd(spa->spa_dsl_pool->dp_bptree_obj);
	mos_obj_refd(spa->spa_dsl_pool->dp_tmp_userrefs_obj);
	mos_obj_refd(spa->spa_dsl_pool->dp_scan->scn_phys.scn_queue_obj);
	bpobj_count_refd(&spa->spa_deferred_bpobj);
	mos_obj_refd(dp->dp_empty_bpobj);
	bpobj_count_refd(&dp->dp_obsolete_bpobj);
	bpobj_count_refd(&dp->dp_free_bpobj);
	mos_obj_refd(spa->spa_l2cache.sav_object);
	mos_obj_refd(spa->spa_spares.sav_object);

	mos_obj_refd(spa->spa_condensing_indirect_phys.
	    scip_next_mapping_object);
	mos_obj_refd(spa->spa_condensing_indirect_phys.
	    scip_prev_obsolete_sm_object);
	if (spa->spa_condensing_indirect_phys.scip_next_mapping_object != 0) {
		vdev_indirect_mapping_t *vim =
		    vdev_indirect_mapping_open(mos,
		    spa->spa_condensing_indirect_phys.scip_next_mapping_object);
		mos_obj_refd(vim->vim_phys->vimp_counts_object);
		vdev_indirect_mapping_close(vim);
	}

	if (dp->dp_origin_snap != NULL) {
		dsl_dataset_t *ds;

		dsl_pool_config_enter(dp, FTAG);
		VERIFY0(dsl_dataset_hold_obj(dp,
		    dsl_dataset_phys(dp->dp_origin_snap)->ds_next_snap_obj,
		    FTAG, &ds));
		count_ds_mos_objects(ds);
		dump_deadlist(&ds->ds_deadlist);
		dsl_dataset_rele(ds, FTAG);
		dsl_pool_config_exit(dp, FTAG);

		count_ds_mos_objects(dp->dp_origin_snap);
		dump_deadlist(&dp->dp_origin_snap->ds_deadlist);
	}
	count_dir_mos_objects(dp->dp_mos_dir);
	if (dp->dp_free_dir != NULL)
		count_dir_mos_objects(dp->dp_free_dir);
	if (dp->dp_leak_dir != NULL)
		count_dir_mos_objects(dp->dp_leak_dir);

	mos_leak_vdev(spa->spa_root_vdev);

	for (uint64_t class = 0; class < DDT_CLASSES; class++) {
		for (uint64_t type = 0; type < DDT_TYPES; type++) {
			for (uint64_t cksum = 0;
			    cksum < ZIO_CHECKSUM_FUNCTIONS; cksum++) {
				ddt_t *ddt = spa->spa_ddt[cksum];
				mos_obj_refd(ddt->ddt_object[type][class]);
			}
		}
	}

	/*
	 * Visit all allocated objects and make sure they are referenced.
	 */
	uint64_t object = 0;
	while (dmu_object_next(mos, &object, B_FALSE, 0) == 0) {
		if (range_tree_contains(mos_refd_objs, object, 1)) {
			range_tree_remove(mos_refd_objs, object, 1);
		} else {
			dmu_object_info_t doi;
			const char *name;
			dmu_object_info(mos, object, &doi);
			if (doi.doi_type & DMU_OT_NEWTYPE) {
				dmu_object_byteswap_t bswap =
				    DMU_OT_BYTESWAP(doi.doi_type);
				name = dmu_ot_byteswap[bswap].ob_name;
			} else {
				name = dmu_ot[doi.doi_type].ot_name;
			}

			(void) printf("MOS object %llu (%s) leaked\n",
			    (u_longlong_t)object, name);
			rv = 2;
		}
	}
	(void) range_tree_walk(mos_refd_objs, mos_leaks_cb, NULL);
	if (!range_tree_is_empty(mos_refd_objs))
		rv = 2;
	range_tree_vacate(mos_refd_objs, NULL, NULL);
	range_tree_destroy(mos_refd_objs);
	return (rv);
}