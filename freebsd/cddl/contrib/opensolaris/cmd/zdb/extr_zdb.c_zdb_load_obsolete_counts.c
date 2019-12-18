#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ vdev_id; int /*<<< orphan*/  vdev_asize; int /*<<< orphan*/ * vdev_obsolete_sm; TYPE_2__* vdev_spa; int /*<<< orphan*/ * vdev_indirect_mapping; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  vdev_indirect_mapping_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  space_map_t ;
struct TYPE_8__ {scalar_t__ scip_vdev; scalar_t__ scip_prev_obsolete_sm_object; } ;
struct TYPE_7__ {int /*<<< orphan*/  spa_meta_objset; TYPE_3__ spa_condensing_indirect_phys; } ;
typedef  TYPE_2__ spa_t ;
typedef  TYPE_3__ spa_condensing_indirect_phys_t ;

/* Variables and functions */
 int /*<<< orphan*/  EQUIV (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  space_map_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  space_map_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  space_map_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vdev_indirect_mapping_load_obsolete_counts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_indirect_mapping_load_obsolete_spacemap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vdev_obsolete_sm_object (TYPE_1__*) ; 

__attribute__((used)) static uint32_t *
zdb_load_obsolete_counts(vdev_t *vd)
{
	vdev_indirect_mapping_t *vim = vd->vdev_indirect_mapping;
	spa_t *spa = vd->vdev_spa;
	spa_condensing_indirect_phys_t *scip =
	    &spa->spa_condensing_indirect_phys;
	uint32_t *counts;

	EQUIV(vdev_obsolete_sm_object(vd) != 0, vd->vdev_obsolete_sm != NULL);
	counts = vdev_indirect_mapping_load_obsolete_counts(vim);
	if (vd->vdev_obsolete_sm != NULL) {
		vdev_indirect_mapping_load_obsolete_spacemap(vim, counts,
		    vd->vdev_obsolete_sm);
	}
	if (scip->scip_vdev == vd->vdev_id &&
	    scip->scip_prev_obsolete_sm_object != 0) {
		space_map_t *prev_obsolete_sm = NULL;
		VERIFY0(space_map_open(&prev_obsolete_sm, spa->spa_meta_objset,
		    scip->scip_prev_obsolete_sm_object, 0, vd->vdev_asize, 0));
		space_map_update(prev_obsolete_sm);
		vdev_indirect_mapping_load_obsolete_spacemap(vim, counts,
		    prev_obsolete_sm);
		space_map_close(prev_obsolete_sm);
	}
	return (counts);
}