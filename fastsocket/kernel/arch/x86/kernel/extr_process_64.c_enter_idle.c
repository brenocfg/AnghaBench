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
 int /*<<< orphan*/  IDLE_START ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idle_notifier ; 
 int /*<<< orphan*/  is_idle ; 
 int /*<<< orphan*/  percpu_write (int /*<<< orphan*/ ,int) ; 

void enter_idle(void)
{
	percpu_write(is_idle, 1);
	atomic_notifier_call_chain(&idle_notifier, IDLE_START, NULL);
}