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
 int /*<<< orphan*/  profile_timer_exceptions_nb ; 
 int /*<<< orphan*/  synchronize_sched () ; 
 int /*<<< orphan*/  unregister_die_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void timer_stop(void)
{
	unregister_die_notifier(&profile_timer_exceptions_nb);
	synchronize_sched();  /* Allow already-started NMIs to complete. */
}