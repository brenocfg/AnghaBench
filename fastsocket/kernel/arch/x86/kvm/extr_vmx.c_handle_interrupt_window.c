#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  irq_window_exits; } ;
struct kvm_vcpu {TYPE_2__* run; int /*<<< orphan*/  kvm; TYPE_1__ stat; } ;
struct TYPE_4__ {int /*<<< orphan*/  exit_reason; scalar_t__ request_interrupt_window; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_BASED_VIRTUAL_INTR_PENDING ; 
 int /*<<< orphan*/  CPU_BASED_VM_EXEC_CONTROL ; 
 int /*<<< orphan*/  KVM_EXIT_IRQ_WINDOW_OPEN ; 
 int /*<<< orphan*/  irqchip_in_kernel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_cpu_has_interrupt (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_interrupt_window(struct kvm_vcpu *vcpu)
{
	u32 cpu_based_vm_exec_control;

	/* clear pending irq */
	cpu_based_vm_exec_control = vmcs_read32(CPU_BASED_VM_EXEC_CONTROL);
	cpu_based_vm_exec_control &= ~CPU_BASED_VIRTUAL_INTR_PENDING;
	vmcs_write32(CPU_BASED_VM_EXEC_CONTROL, cpu_based_vm_exec_control);

	++vcpu->stat.irq_window_exits;

	/*
	 * If the user space waits to inject interrupts, exit as soon as
	 * possible
	 */
	if (!irqchip_in_kernel(vcpu->kvm) &&
	    vcpu->run->request_interrupt_window &&
	    !kvm_cpu_has_interrupt(vcpu)) {
		vcpu->run->exit_reason = KVM_EXIT_IRQ_WINDOW_OPEN;
		return 0;
	}
	return 1;
}