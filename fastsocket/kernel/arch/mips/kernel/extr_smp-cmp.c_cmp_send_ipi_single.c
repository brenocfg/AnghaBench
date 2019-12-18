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
#define  SMP_CALL_FUNCTION 129 
#define  SMP_RESCHEDULE_YOURSELF 128 
 int /*<<< orphan*/  ipi_call_function (int) ; 
 int /*<<< orphan*/  ipi_resched (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void cmp_send_ipi_single(int cpu, unsigned int action)
{
	unsigned long flags;

	local_irq_save(flags);

	switch (action) {
	case SMP_CALL_FUNCTION:
		ipi_call_function(cpu);
		break;

	case SMP_RESCHEDULE_YOURSELF:
		ipi_resched(cpu);
		break;
	}

	local_irq_restore(flags);
}