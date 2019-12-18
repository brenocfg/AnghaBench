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
struct physdev_irq {int irq; int vector; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ HYPERVISOR_physdev_op (int /*<<< orphan*/ ,struct physdev_irq*) ; 
 int /*<<< orphan*/  PHYSDEVOP_alloc_irq_vector ; 

__attribute__((used)) static int
xen_assign_irq_vector(int irq)
{
	struct physdev_irq irq_op;

	irq_op.irq = irq;
	if (HYPERVISOR_physdev_op(PHYSDEVOP_alloc_irq_vector, &irq_op))
		return -ENOSPC;

	return irq_op.vector;
}