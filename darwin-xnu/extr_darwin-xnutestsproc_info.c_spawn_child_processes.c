#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_config_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  (* child_action_handler_t ) (TYPE_1__*,int) ;
struct TYPE_6__ {int child_count; int /*<<< orphan*/ * parent_pipe; int /*<<< orphan*/ ** child_pipe; int /*<<< orphan*/ * child_pids; scalar_t__ cow_map; int /*<<< orphan*/  proc_grp_id; } ;

/* Variables and functions */
 int MAP_ANON ; 
 int /*<<< orphan*/  MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 size_t PIPE_IN ; 
 size_t PIPE_OUT ; 
 int /*<<< orphan*/  PROT_WRITE ; 
 int /*<<< orphan*/  T_ASSERT_NE_PTR (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*,...) ; 
 int /*<<< orphan*/  T_LOG (char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  WAIT_FOR_CHILDREN (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  getpgid (int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int) ; 
 scalar_t__ mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int pipe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setpgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static proc_config_t
spawn_child_processes(int child_count, child_action_handler_t child_handler)
{
	/*
	 * Spawn procs for Tests 1.2 and 1.3
	 */
	T_LOG("Spawning child processes...");
	proc_config_t proc_config = malloc(sizeof(*proc_config));
	int action                = 0;
	int err;

	setpgid(0, 0);
	proc_config->proc_grp_id = getpgid(0);

	proc_config->child_count = child_count;

	err = pipe(proc_config->parent_pipe);
	T_QUIET;
	T_ASSERT_POSIX_SUCCESS(err, "pipe() call");

	/*
	 * Needed for ACT_PHASE3 tests
	 */
	proc_config->cow_map = mmap(0, PAGE_SIZE, PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	T_QUIET;
	T_ASSERT_NE_PTR(proc_config->cow_map, MAP_FAILED, "cow_map mmap()");
	*((int *)(proc_config->cow_map)) = 10;

	pid_t child_pid;
	int i;
	int child_id;
	for (i = 0; i < child_count; i++) {
		err = pipe(proc_config->child_pipe[i]);
		T_QUIET;
		T_ASSERT_POSIX_SUCCESS(err, "pipe() call");

		child_pid = fork();
		child_id  = i;
		T_QUIET;
		T_ASSERT_POSIX_SUCCESS(child_pid, "fork() in parent process for child %d", child_id);

		if (child_pid == 0) {
			child_handler(proc_config, child_id);
		} else {
			proc_config->child_pids[child_id] = child_pid;
		}
		close(proc_config->child_pipe[child_id][PIPE_IN]);
	}
	/*
	 * Wait for the children processes to spawn
	 */
	close(proc_config->parent_pipe[PIPE_OUT]);
	WAIT_FOR_CHILDREN(proc_config->parent_pipe[PIPE_IN], action, child_count);

	return proc_config;
}