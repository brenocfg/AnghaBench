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
 int /*<<< orphan*/  TIF_SIGPENDING ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  do_signal () ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ test_tsk_thread_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void interrupt_end(void)
{
	if (need_resched())
		schedule();
	if (test_tsk_thread_flag(current, TIF_SIGPENDING))
		do_signal();
}