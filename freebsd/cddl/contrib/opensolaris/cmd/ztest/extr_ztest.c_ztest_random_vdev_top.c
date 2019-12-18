#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__** vdev_child; int /*<<< orphan*/  vdev_children; TYPE_1__* vdev_mg; scalar_t__ vdev_islog; } ;
typedef  TYPE_2__ vdev_t ;
typedef  size_t uint64_t ;
struct TYPE_9__ {TYPE_2__* spa_root_vdev; } ;
typedef  TYPE_3__ spa_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_7__ {int /*<<< orphan*/ * mg_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 scalar_t__ spa_config_held (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_is_concrete (TYPE_2__*) ; 
 size_t ztest_random (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
ztest_random_vdev_top(spa_t *spa, boolean_t log_ok)
{
	uint64_t top;
	vdev_t *rvd = spa->spa_root_vdev;
	vdev_t *tvd;

	ASSERT(spa_config_held(spa, SCL_ALL, RW_READER) != 0);

	do {
		top = ztest_random(rvd->vdev_children);
		tvd = rvd->vdev_child[top];
	} while (!vdev_is_concrete(tvd) || (tvd->vdev_islog && !log_ok) ||
	    tvd->vdev_mg == NULL || tvd->vdev_mg->mg_class == NULL);

	return (top);
}