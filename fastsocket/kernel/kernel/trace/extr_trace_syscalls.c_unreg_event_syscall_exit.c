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
struct syscall_metadata {char* name; } ;
struct ftrace_event_call {scalar_t__ data; } ;

/* Variables and functions */
 int NR_syscalls ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enabled_exit_syscalls ; 
 int /*<<< orphan*/  ftrace_syscall_exit ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sys_refcount_exit ; 
 int syscall_name_to_nr (char const*) ; 
 int /*<<< orphan*/  syscall_trace_lock ; 
 int /*<<< orphan*/  unregister_trace_sys_exit (int /*<<< orphan*/ ) ; 

void unreg_event_syscall_exit(struct ftrace_event_call *call)
{
	int num;
	const char *name;

	name = ((struct syscall_metadata *)call->data)->name;
	num = syscall_name_to_nr(name);
	if (num < 0 || num >= NR_syscalls)
		return;
	mutex_lock(&syscall_trace_lock);
	sys_refcount_exit--;
	clear_bit(num, enabled_exit_syscalls);
	if (!sys_refcount_exit)
		unregister_trace_sys_exit(ftrace_syscall_exit);
	mutex_unlock(&syscall_trace_lock);
}