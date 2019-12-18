#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_2__ {int zo_verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCL_NONE ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ spa_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_vdev_state_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_vdev_state_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zio_resume (int /*<<< orphan*/ *) ; 
 TYPE_1__ ztest_opts ; 

__attribute__((used)) static void
ztest_resume(spa_t *spa)
{
	if (spa_suspended(spa) && ztest_opts.zo_verbose >= 6)
		(void) printf("resuming from suspended state\n");
	spa_vdev_state_enter(spa, SCL_NONE);
	vdev_clear(spa, NULL);
	(void) spa_vdev_state_exit(spa, NULL, 0);
	(void) zio_resume(spa);
}