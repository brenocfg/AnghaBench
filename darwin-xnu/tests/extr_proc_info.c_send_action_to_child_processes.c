#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_config_t ;
typedef  int /*<<< orphan*/  action ;
struct TYPE_3__ {int child_count; int /*<<< orphan*/ * parent_pipe; int /*<<< orphan*/ ** child_pipe; } ;

/* Variables and functions */
 int ACT_EXIT ; 
 size_t PIPE_IN ; 
 size_t PIPE_OUT ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (long,char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  WAIT_FOR_CHILDREN (int /*<<< orphan*/ ,int,int) ; 
 long write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
send_action_to_child_processes(proc_config_t proc_config, int action)
{
	long err;
	for (int i = 0; i < proc_config->child_count; i++) {
		err = write(proc_config->child_pipe[i][PIPE_OUT], &action, sizeof(action));
		T_QUIET;
		T_ASSERT_POSIX_SUCCESS(err, "write() to child in send_action");
	}
	if (action != ACT_EXIT) {
		WAIT_FOR_CHILDREN(proc_config->parent_pipe[PIPE_IN], action, proc_config->child_count);
	}
}