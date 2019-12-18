#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  kmemleak_enabled ; 
 int kthread_should_stop () ; 
 int signal_pending (TYPE_1__*) ; 

__attribute__((used)) static int scan_should_stop(void)
{
	if (!atomic_read(&kmemleak_enabled))
		return 1;

	/*
	 * This function may be called from either process or kthread context,
	 * hence the need to check for both stop conditions.
	 */
	if (current->mm)
		return signal_pending(current);
	else
		return kthread_should_stop();

	return 0;
}