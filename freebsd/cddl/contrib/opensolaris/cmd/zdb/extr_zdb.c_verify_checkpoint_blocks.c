#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  spa_name; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  fatal (char*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* import_checkpointed_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int spa_open (char*,TYPE_1__**,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  verify_checkpoint_ms_spacemaps (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  verify_checkpoint_vdev_spacemaps (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void
verify_checkpoint_blocks(spa_t *spa)
{
	spa_t *checkpoint_spa;
	char *checkpoint_pool;
	nvlist_t *config = NULL;
	int error = 0;

	/*
	 * We import the checkpointed state of the pool (under a different
	 * name) so we can do verification on it against the current state
	 * of the pool.
	 */
	checkpoint_pool = import_checkpointed_state(spa->spa_name, config,
	    NULL);
	ASSERT(strcmp(spa->spa_name, checkpoint_pool) != 0);

	error = spa_open(checkpoint_pool, &checkpoint_spa, FTAG);
	if (error != 0) {
		fatal("Tried to open pool \"%s\" but spa_open() failed with "
		    "error %d\n", checkpoint_pool, error);
	}

	/*
	 * Ensure that ranges in the checkpoint space maps of each vdev
	 * are allocated according to the checkpointed state's metaslab
	 * space maps.
	 */
	verify_checkpoint_vdev_spacemaps(checkpoint_spa, spa);

	/*
	 * Ensure that allocated ranges in the checkpoint's metaslab
	 * space maps remain allocated in the metaslab space maps of
	 * the current state.
	 */
	verify_checkpoint_ms_spacemaps(checkpoint_spa, spa);

	/*
	 * Once we are done, we get rid of the checkpointed state.
	 */
	spa_close(checkpoint_spa, FTAG);
	free(checkpoint_pool);
}