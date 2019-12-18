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
 int /*<<< orphan*/  P1275_INOUT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  p1275_cmd (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_capture () ; 
 int /*<<< orphan*/  smp_release () ; 

void prom_cmdline(void)
{
	unsigned long flags;

	local_irq_save(flags);

#ifdef CONFIG_SMP
	smp_capture();
#endif

	p1275_cmd("enter", P1275_INOUT(0, 0));

#ifdef CONFIG_SMP
	smp_release();
#endif

	local_irq_restore(flags);
}