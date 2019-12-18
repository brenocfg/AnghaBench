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
struct irqaction {int dummy; } ;
typedef  int /*<<< orphan*/  ia64_vector ;

/* Variables and functions */
 int /*<<< orphan*/  __xen_register_percpu_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct irqaction*,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void
xen_register_percpu_irq(ia64_vector vec, struct irqaction *action)
{
	__xen_register_percpu_irq(smp_processor_id(), vec, action, 1);
}