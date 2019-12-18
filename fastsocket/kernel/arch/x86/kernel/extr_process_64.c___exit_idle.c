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
 int /*<<< orphan*/  IDLE_END ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idle_notifier ; 
 int /*<<< orphan*/  is_idle ; 
 scalar_t__ x86_test_and_clear_bit_percpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __exit_idle(void)
{
	if (x86_test_and_clear_bit_percpu(0, is_idle) == 0)
		return;
	atomic_notifier_call_chain(&idle_notifier, IDLE_END, NULL);
}