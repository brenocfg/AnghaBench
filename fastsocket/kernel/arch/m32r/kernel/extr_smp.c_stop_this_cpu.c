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
 int /*<<< orphan*/  M32R_ICU_IMASK_PORTL ; 
 int /*<<< orphan*/  cpu_clear (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_online_map ; 
 int /*<<< orphan*/  inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 

__attribute__((used)) static void stop_this_cpu(void *dummy)
{
	int cpu_id = smp_processor_id();

	/*
	 * Remove this CPU:
	 */
	cpu_clear(cpu_id, cpu_online_map);

	/*
	 * PSW IE = 1;
	 * IMASK = 0;
	 * goto SLEEP
	 */
	local_irq_disable();
	outl(0, M32R_ICU_IMASK_PORTL);
	inl(M32R_ICU_IMASK_PORTL);	/* dummy read */
	local_irq_enable();

	for ( ; ; );
}