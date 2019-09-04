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
 int /*<<< orphan*/  ASYNC ; 
 int /*<<< orphan*/  MP_CALL_PM ; 
 int /*<<< orphan*/  assert (int) ; 
 int cpu_number () ; 
 int /*<<< orphan*/  i386_signal_cpu (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  mp_PM_func () ; 

void
cpu_PM_interrupt(int cpu)
{
	assert(!ml_get_interrupts_enabled());

	if (mp_PM_func != NULL) {
		if (cpu == cpu_number())
			mp_PM_func();
		else
			i386_signal_cpu(cpu, MP_CALL_PM, ASYNC);
	}
}