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
typedef  int /*<<< orphan*/  posix_spawnattr_t ;
typedef  int pid_t ;

/* Variables and functions */
 int EX_OK ; 
 int /*<<< orphan*/  POSIX_SPAWN_START_SUSPENDED ; 
 int SIGKILL ; 
 int /*<<< orphan*/  T_ASSERT_EQ (int,int,char*) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int WEXITSTATUS (int) ; 
 int WIFEXITED (int) ; 
 int WIFSIGNALED (int) ; 
 int WIFSTOPPED (int) ; 
 int WNOHANG ; 
 int WTERMSIG (int) ; 
 int WUNTRACED ; 
 int /*<<< orphan*/  _IONBF ; 
 int kill (int,int) ; 
 int posix_spawn (int*,char* const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char* const*,char**) ; 
 int posix_spawnattr_destroy (int /*<<< orphan*/ *) ; 
 int posix_spawnattr_init (int /*<<< orphan*/ *) ; 
 int posix_spawnattr_setflags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int waitpid (int,int*,int) ; 

__attribute__((used)) static void
spawn_and_signal(int signal)
{
	/* do not buffer output to stdout */
	setvbuf(stdout, NULL, _IONBF, 0);

	int ret;
	posix_spawnattr_t attr;

	ret = posix_spawnattr_init(&attr);
	T_QUIET;
	T_ASSERT_POSIX_SUCCESS(ret, "posix_spawnattr_init");

	ret = posix_spawnattr_setflags(&attr, POSIX_SPAWN_START_SUSPENDED);
	T_QUIET;
	T_ASSERT_POSIX_SUCCESS(ret, "posix_spawnattr_setflags");

	char * const    prog = "/usr/bin/true";
	char * const    argv_child[] = { prog, NULL };
	pid_t           child_pid;
	extern char   **environ;

	ret = posix_spawn(&child_pid, prog, NULL, &attr, argv_child, environ);
	T_ASSERT_POSIX_SUCCESS(ret, "posix_spawn");

	printf("parent: spawned child with pid %d\n", child_pid);

	ret = posix_spawnattr_destroy(&attr);
	T_QUIET;
	T_ASSERT_POSIX_SUCCESS(ret, "posix_spawnattr_destroy");

	int status = 0;
	int waitpid_result = waitpid(child_pid, &status, WUNTRACED|WNOHANG);
	T_ASSERT_POSIX_SUCCESS(waitpid_result, "waitpid");

	T_ASSERT_EQ(waitpid_result, child_pid, "waitpid should return child we spawned");

	T_ASSERT_EQ(WIFEXITED(status), 0, "before SIGCONT: must not have exited");
	T_ASSERT_EQ(WIFSTOPPED(status), 1, "before SIGCONT: must be stopped");

	printf("parent: continuing child process\n");

	ret = kill(child_pid, signal);
	T_ASSERT_POSIX_SUCCESS(ret, "kill(signal)");

	printf("parent: waiting for child process\n");

	status = 0;
	waitpid_result = waitpid(child_pid, &status, 0);
	T_ASSERT_POSIX_SUCCESS(waitpid_result, "waitpid");

	T_ASSERT_EQ(waitpid_result, child_pid, "waitpid should return child we spawned");

	if (signal == SIGKILL) {
		T_ASSERT_EQ(WIFSIGNALED(status), 1, "child should have exited due to signal");
		T_ASSERT_EQ(WTERMSIG(status), SIGKILL, "child should have exited due to SIGKILL");
	} else {
		T_ASSERT_EQ(WIFEXITED(status), 1, "child should have exited normally");
		T_ASSERT_EQ(WEXITSTATUS(status), EX_OK, "child should have exited with success");
	}

	printf("wait returned with pid %d, status %d\n", ret, status);
}