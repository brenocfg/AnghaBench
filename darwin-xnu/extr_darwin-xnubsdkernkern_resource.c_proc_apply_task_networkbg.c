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
typedef  int /*<<< orphan*/  thread_t ;
typedef  void* proc_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 void* PROC_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  do_background_socket (void*,int /*<<< orphan*/ ) ; 
 void* proc_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_pid (void*) ; 
 int /*<<< orphan*/  proc_rele (void*) ; 

void
proc_apply_task_networkbg(void * bsd_info, thread_t thread)
{
	assert(bsd_info != PROC_NULL);

	pid_t pid = proc_pid((proc_t)bsd_info);

	proc_t p = proc_find(pid);

	if (p != PROC_NULL) {
		assert(p == (proc_t)bsd_info);

		do_background_socket(p, thread);
		proc_rele(p);
	}
}