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
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* spa_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/ * spa_next (int /*<<< orphan*/ *) ; 
 TYPE_1__ ztest_opts ; 

__attribute__((used)) static void
ztest_walk_pool_directory(char *header)
{
	spa_t *spa = NULL;

	if (ztest_opts.zo_verbose >= 6)
		(void) printf("%s\n", header);

	mutex_enter(&spa_namespace_lock);
	while ((spa = spa_next(spa)) != NULL)
		if (ztest_opts.zo_verbose >= 6)
			(void) printf("\t%s\n", spa_name(spa));
	mutex_exit(&spa_namespace_lock);
}