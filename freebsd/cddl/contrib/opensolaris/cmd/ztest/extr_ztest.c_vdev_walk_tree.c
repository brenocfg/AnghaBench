#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t vdev_children; struct TYPE_10__** vdev_child; TYPE_1__* vdev_ops; } ;
typedef  TYPE_2__ vdev_t ;
typedef  size_t uint_t ;
struct TYPE_9__ {scalar_t__ vdev_op_leaf; } ;

/* Variables and functions */

vdev_t *
vdev_walk_tree(vdev_t *vd, vdev_t *(*func)(vdev_t *, void *), void *arg)
{
	if (vd->vdev_ops->vdev_op_leaf) {
		if (func == NULL)
			return (vd);
		else
			return (func(vd, arg));
	}

	for (uint_t c = 0; c < vd->vdev_children; c++) {
		vdev_t *cvd = vd->vdev_child[c];
		if ((cvd = vdev_walk_tree(cvd, func, arg)) != NULL)
			return (cvd);
	}
	return (NULL);
}