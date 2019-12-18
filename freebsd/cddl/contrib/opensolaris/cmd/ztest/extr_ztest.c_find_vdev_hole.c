#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int vdev_children; scalar_t__ vdev_ishole; struct TYPE_5__** vdev_child; } ;
typedef  TYPE_1__ vdev_t ;
struct TYPE_6__ {TYPE_1__* spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  RW_READER ; 
 scalar_t__ SCL_VDEV ; 
 scalar_t__ spa_config_held (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 

int
find_vdev_hole(spa_t *spa)
{
	vdev_t *rvd = spa->spa_root_vdev;
	int c;

	ASSERT(spa_config_held(spa, SCL_VDEV, RW_READER) == SCL_VDEV);

	for (c = 0; c < rvd->vdev_children; c++) {
		vdev_t *cvd = rvd->vdev_child[c];

		if (cvd->vdev_ishole)
			break;
	}
	return (c);
}