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
 int need_resched () ; 
 int /*<<< orphan*/  preempt_disable_notrace () ; 

__attribute__((used)) static inline int ftrace_preempt_disable(void)
{
	int resched;

	resched = need_resched();
	preempt_disable_notrace();

	return resched;
}