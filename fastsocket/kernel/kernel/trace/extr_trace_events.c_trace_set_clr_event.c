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
 int __ftrace_set_clr_event (int /*<<< orphan*/ *,char const*,char const*,int) ; 

int trace_set_clr_event(const char *system, const char *event, int set)
{
	return __ftrace_set_clr_event(NULL, system, event, set);
}