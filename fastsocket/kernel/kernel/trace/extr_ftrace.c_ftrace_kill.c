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
 int /*<<< orphan*/  clear_ftrace_function () ; 
 int ftrace_disabled ; 
 scalar_t__ ftrace_enabled ; 

void ftrace_kill(void)
{
	ftrace_disabled = 1;
	ftrace_enabled = 0;
	clear_ftrace_function();
}