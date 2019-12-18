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
typedef  int /*<<< orphan*/  ztest_shared_t ;
struct TYPE_2__ {int zo_init; int zo_verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_path ; 
 int /*<<< orphan*/  ztest_init (int /*<<< orphan*/ *) ; 
 TYPE_1__ ztest_opts ; 
 int /*<<< orphan*/ * ztest_shared ; 

__attribute__((used)) static void
ztest_run_init(void)
{
	ztest_shared_t *zs = ztest_shared;

	ASSERT(ztest_opts.zo_init != 0);

	/*
	 * Blow away any existing copy of zpool.cache
	 */
	(void) remove(spa_config_path);

	/*
	 * Create and initialize our storage pool.
	 */
	for (int i = 1; i <= ztest_opts.zo_init; i++) {
		bzero(zs, sizeof (ztest_shared_t));
		if (ztest_opts.zo_verbose >= 3 &&
		    ztest_opts.zo_init != 1) {
			(void) printf("ztest_init(), pass %d\n", i);
		}
		ztest_init(zs);
	}
}