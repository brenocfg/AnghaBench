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
 int /*<<< orphan*/  PREEMPT_ACTIVE ; 
 int /*<<< orphan*/  add_preempt_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  sub_preempt_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __cond_resched(void)
{
	add_preempt_count(PREEMPT_ACTIVE);
	schedule();
	sub_preempt_count(PREEMPT_ACTIVE);
}