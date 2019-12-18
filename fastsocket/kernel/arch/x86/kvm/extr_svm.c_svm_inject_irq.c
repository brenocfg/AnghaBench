#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmcb_control_area {int int_vector; int int_ctl; } ;
struct vcpu_svm {TYPE_1__* vmcb; } ;
struct TYPE_2__ {struct vmcb_control_area control; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCB_INTR ; 
 int V_INTR_PRIO_MASK ; 
 int V_INTR_PRIO_SHIFT ; 
 int V_IRQ_MASK ; 
 int /*<<< orphan*/  mark_dirty (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void svm_inject_irq(struct vcpu_svm *svm, int irq)
{
	struct vmcb_control_area *control;

	control = &svm->vmcb->control;
	control->int_vector = irq;
	control->int_ctl &= ~V_INTR_PRIO_MASK;
	control->int_ctl |= V_IRQ_MASK |
		((/*control->int_vector >> 4*/ 0xf) << V_INTR_PRIO_SHIFT);
	mark_dirty(svm->vmcb, VMCB_INTR);
}