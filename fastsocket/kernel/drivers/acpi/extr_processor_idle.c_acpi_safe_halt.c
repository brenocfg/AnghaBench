#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  TS_POLLING ; 
 TYPE_1__* current_thread_info () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  safe_halt () ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static void acpi_safe_halt(void)
{
	current_thread_info()->status &= ~TS_POLLING;
	/*
	 * TS_POLLING-cleared state must be visible before we
	 * test NEED_RESCHED:
	 */
	smp_mb();
	if (!need_resched()) {
		safe_halt();
		local_irq_disable();
	}
	current_thread_info()->status |= TS_POLLING;
}