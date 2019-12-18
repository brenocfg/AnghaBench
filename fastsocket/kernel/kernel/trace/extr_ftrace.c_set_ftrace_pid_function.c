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
typedef  scalar_t__ ftrace_func_t ;

/* Variables and functions */
 scalar_t__ ftrace_pid_func ; 
 scalar_t__ ftrace_pid_function ; 

__attribute__((used)) static void set_ftrace_pid_function(ftrace_func_t func)
{
	/* do not set ftrace_pid_function to itself! */
	if (func != ftrace_pid_func)
		ftrace_pid_function = func;
}