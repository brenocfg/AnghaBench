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
struct pid {int dummy; } ;

/* Variables and functions */
 struct pid* ftrace_swapper_pid ; 
 int /*<<< orphan*/  set_ftrace_pid (struct pid*) ; 
 int /*<<< orphan*/  set_ftrace_swapper () ; 

__attribute__((used)) static void set_ftrace_pid_task(struct pid *pid)
{
	if (pid == ftrace_swapper_pid)
		set_ftrace_swapper();
	else
		set_ftrace_pid(pid);
}