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
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_thermal_count ; 
 int /*<<< orphan*/  smp_thermal_vector () ; 

__attribute__((used)) static inline void __smp_thermal_interrupt(void)
{
	inc_irq_stat(irq_thermal_count);
	smp_thermal_vector();
}