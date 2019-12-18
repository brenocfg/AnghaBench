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
struct irq_work {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_WORK_BUSY ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ irq_work_is_set (struct irq_work*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqs_disabled () ; 

void irq_work_sync(struct irq_work *entry)
{
	WARN_ON_ONCE(irqs_disabled());

	while (irq_work_is_set(entry, IRQ_WORK_BUSY))
		cpu_relax();
}