#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ vdev_top_zap; size_t vdev_children; struct TYPE_3__** vdev_child; int /*<<< orphan*/  vdev_spa; struct TYPE_3__* vdev_top; } ;
typedef  TYPE_1__ vdev_t ;
typedef  size_t uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  VDEV_TOP_ZAP_POOL_CHECKPOINT_SM ; 
 int /*<<< orphan*/  spa_meta_objset (int /*<<< orphan*/ ) ; 
 scalar_t__ zap_contains (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_checkpoint_refcount(vdev_t *vd)
{
	int refcount = 0;

	if (vd->vdev_top == vd && vd->vdev_top_zap != 0 &&
	    zap_contains(spa_meta_objset(vd->vdev_spa),
	    vd->vdev_top_zap, VDEV_TOP_ZAP_POOL_CHECKPOINT_SM) == 0)
		refcount++;

	for (uint64_t c = 0; c < vd->vdev_children; c++)
		refcount += get_checkpoint_refcount(vd->vdev_child[c]);

	return (refcount);
}