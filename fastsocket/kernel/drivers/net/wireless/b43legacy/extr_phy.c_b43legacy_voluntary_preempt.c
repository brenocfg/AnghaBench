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
 int /*<<< orphan*/  B43legacy_BUG_ON (int) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  in_atomic () ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  in_irq () ; 
 int /*<<< orphan*/  irqs_disabled () ; 

__attribute__((used)) static inline
void b43legacy_voluntary_preempt(void)
{
	B43legacy_BUG_ON(!(!in_atomic() && !in_irq() &&
			  !in_interrupt() && !irqs_disabled()));
#ifndef CONFIG_PREEMPT
	cond_resched();
#endif /* CONFIG_PREEMPT */
}