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
 unsigned int MIPS_CPU_IRQ_BASE ; 
 int /*<<< orphan*/  clear_c0_cause (int) ; 
 unsigned int dvpe () ; 
 int /*<<< orphan*/  evpe (unsigned int) ; 
 int /*<<< orphan*/  unmask_mips_mt_irq (unsigned int) ; 

__attribute__((used)) static unsigned int mips_mt_cpu_irq_startup(unsigned int irq)
{
	unsigned int vpflags = dvpe();

	clear_c0_cause(0x100 << (irq - MIPS_CPU_IRQ_BASE));
	evpe(vpflags);
	unmask_mips_mt_irq(irq);

	return 0;
}