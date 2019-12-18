#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ztest_ds_t ;
struct TYPE_10__ {int vdev_guid; int /*<<< orphan*/ * vdev_initialize_thread; int /*<<< orphan*/  vdev_path; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int uint64_t ;
struct TYPE_11__ {int /*<<< orphan*/  spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_12__ {int zo_verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
#define  POOL_INITIALIZE_CANCEL 130 
#define  POOL_INITIALIZE_DO 129 
 int /*<<< orphan*/  POOL_INITIALIZE_FUNCS ; 
#define  POOL_INITIALIZE_SUSPEND 128 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_VDEV ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spa_vdev_initialize (TYPE_2__*,int,int) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,TYPE_1__*,int) ; 
 TYPE_5__ ztest_opts ; 
 int ztest_random (int /*<<< orphan*/ ) ; 
 TYPE_1__* ztest_random_concrete_vdev_leaf (int /*<<< orphan*/ ) ; 
 TYPE_2__* ztest_spa ; 
 int /*<<< orphan*/  ztest_vdev_lock ; 

void
ztest_initialize(ztest_ds_t *zd, uint64_t id)
{
	spa_t *spa = ztest_spa;
	int error = 0;

	mutex_enter(&ztest_vdev_lock);

	spa_config_enter(spa, SCL_VDEV, FTAG, RW_READER);

	/* Random leaf vdev */
	vdev_t *rand_vd = ztest_random_concrete_vdev_leaf(spa->spa_root_vdev);
	if (rand_vd == NULL) {
		spa_config_exit(spa, SCL_VDEV, FTAG);
		mutex_exit(&ztest_vdev_lock);
		return;
	}

	/*
	 * The random vdev we've selected may change as soon as we
	 * drop the spa_config_lock. We create local copies of things
	 * we're interested in.
	 */
	uint64_t guid = rand_vd->vdev_guid;
	char *path = strdup(rand_vd->vdev_path);
	boolean_t active = rand_vd->vdev_initialize_thread != NULL;

	zfs_dbgmsg("vd %p, guid %llu", rand_vd, guid);
	spa_config_exit(spa, SCL_VDEV, FTAG);

	uint64_t cmd = ztest_random(POOL_INITIALIZE_FUNCS);
	error = spa_vdev_initialize(spa, guid, cmd);
	switch (cmd) {
	case POOL_INITIALIZE_CANCEL:
		if (ztest_opts.zo_verbose >= 4) {
			(void) printf("Cancel initialize %s", path);
			if (!active)
				(void) printf(" failed (no initialize active)");
			(void) printf("\n");
		}
		break;
	case POOL_INITIALIZE_DO:
		if (ztest_opts.zo_verbose >= 4) {
			(void) printf("Start initialize %s", path);
			if (active && error == 0)
				(void) printf(" failed (already active)");
			else if (error != 0)
				(void) printf(" failed (error %d)", error);
			(void) printf("\n");
		}
		break;
	case POOL_INITIALIZE_SUSPEND:
		if (ztest_opts.zo_verbose >= 4) {
			(void) printf("Suspend initialize %s", path);
			if (!active)
				(void) printf(" failed (no initialize active)");
			(void) printf("\n");
		}
		break;
	}
	free(path);
	mutex_exit(&ztest_vdev_lock);
}