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
 scalar_t__ irqs_disabled () ; 
 scalar_t__ irqs_disabled_flags (unsigned long) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 

__attribute__((used)) static inline void apm_irq_restore(unsigned long flags)
{
	if (irqs_disabled_flags(flags))
		local_irq_disable();
	else if (irqs_disabled())
		local_irq_enable();
}