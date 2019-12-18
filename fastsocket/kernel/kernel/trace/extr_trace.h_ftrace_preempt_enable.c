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
 int /*<<< orphan*/  preempt_enable_no_resched_notrace () ; 
 int /*<<< orphan*/  preempt_enable_notrace () ; 

__attribute__((used)) static inline void ftrace_preempt_enable(int resched)
{
	if (resched)
		preempt_enable_no_resched_notrace();
	else
		preempt_enable_notrace();
}