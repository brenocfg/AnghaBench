#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  T_ASSERT_EQ (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_ZERO (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_LOG (char*,char*) ; 
 int /*<<< orphan*/  environ ; 
 int posix_spawn (int*,char* const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char* const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_sleep_tests ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trigger_sleep(int for_secs) {
	if(!run_sleep_tests) return 0;

	// sleep for 1 seconds each iteration
	char buf[10];
	snprintf(buf, 10, "%d", for_secs);

	T_LOG("Sleepeing for %s seconds...", buf);

	int spawn_ret, pid;
	char *const pmset1_args[] = {"/usr/bin/pmset", "relative", "wake", buf, NULL};
	T_ASSERT_POSIX_ZERO((spawn_ret = posix_spawn(&pid, pmset1_args[0], NULL, NULL, pmset1_args, environ)), NULL);
	
	T_ASSERT_EQ(waitpid(pid, &spawn_ret, 0), pid, NULL);
	T_ASSERT_EQ(spawn_ret, 0, NULL);

	char *const pmset2_args[] = {"/usr/bin/pmset", "sleepnow", NULL};
	T_ASSERT_POSIX_ZERO((spawn_ret = posix_spawn(&pid, pmset2_args[0], NULL, NULL, pmset2_args, environ)), NULL);
	
	T_ASSERT_EQ(waitpid(pid, &spawn_ret, 0), pid, NULL);
	T_ASSERT_EQ(spawn_ret, 0, NULL);

	return 0;
}