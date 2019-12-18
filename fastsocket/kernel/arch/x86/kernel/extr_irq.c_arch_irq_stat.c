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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_err_count ; 
 int /*<<< orphan*/  irq_mis_count ; 

u64 arch_irq_stat(void)
{
	u64 sum = atomic_read(&irq_err_count);

#ifdef CONFIG_X86_IO_APIC
	sum += atomic_read(&irq_mis_count);
#endif
	return sum;
}