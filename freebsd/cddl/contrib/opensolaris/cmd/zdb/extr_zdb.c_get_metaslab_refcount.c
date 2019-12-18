#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t vdev_ms_count; unsigned int vdev_children; struct TYPE_8__** vdev_child; TYPE_2__** vdev_ms; struct TYPE_8__* vdev_top; } ;
typedef  TYPE_3__ vdev_t ;
typedef  size_t uint64_t ;
struct TYPE_9__ {TYPE_1__* sm_dbuf; } ;
typedef  TYPE_4__ space_map_t ;
typedef  int /*<<< orphan*/  space_map_phys_t ;
struct TYPE_7__ {TYPE_4__* ms_sm; } ;
struct TYPE_6__ {int db_size; } ;

/* Variables and functions */

__attribute__((used)) static int
get_metaslab_refcount(vdev_t *vd)
{
	int refcount = 0;

	if (vd->vdev_top == vd) {
		for (uint64_t m = 0; m < vd->vdev_ms_count; m++) {
			space_map_t *sm = vd->vdev_ms[m]->ms_sm;

			if (sm != NULL &&
			    sm->sm_dbuf->db_size == sizeof (space_map_phys_t))
				refcount++;
		}
	}
	for (unsigned c = 0; c < vd->vdev_children; c++)
		refcount += get_metaslab_refcount(vd->vdev_child[c]);

	return (refcount);
}