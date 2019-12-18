#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int int_ctl; int event_inj; int /*<<< orphan*/  event_inj_err; scalar_t__ tsc_offset; int /*<<< orphan*/  int_state; int /*<<< orphan*/  int_vector; int /*<<< orphan*/  exit_int_info; int /*<<< orphan*/  exit_int_info_err; int /*<<< orphan*/  intercept; int /*<<< orphan*/  intercept_exceptions; int /*<<< orphan*/  intercept_dr_write; int /*<<< orphan*/  intercept_dr_read; int /*<<< orphan*/  intercept_cr_write; int /*<<< orphan*/  intercept_cr_read; int /*<<< orphan*/  msrpm_base_pa; } ;
struct TYPE_15__ {int rflags; int /*<<< orphan*/  cpl; int /*<<< orphan*/  dr6; int /*<<< orphan*/  dr7; int /*<<< orphan*/  rip; int /*<<< orphan*/  rsp; int /*<<< orphan*/  rax; int /*<<< orphan*/  cr2; int /*<<< orphan*/  cr3; int /*<<< orphan*/  cr4; int /*<<< orphan*/  cr0; int /*<<< orphan*/  efer; int /*<<< orphan*/  idtr; int /*<<< orphan*/  gdtr; int /*<<< orphan*/  ds; int /*<<< orphan*/  ss; int /*<<< orphan*/  cs; int /*<<< orphan*/  es; } ;
struct vmcb {TYPE_4__ control; TYPE_1__ save; } ;
struct TYPE_17__ {int /*<<< orphan*/  hflags; int /*<<< orphan*/  cr2; int /*<<< orphan*/  cr3; int /*<<< orphan*/  cr4; int /*<<< orphan*/  shadow_efer; } ;
struct TYPE_19__ {TYPE_3__ arch; } ;
struct TYPE_16__ {int /*<<< orphan*/  intercept; int /*<<< orphan*/  intercept_exceptions; int /*<<< orphan*/  intercept_dr_write; int /*<<< orphan*/  intercept_dr_read; int /*<<< orphan*/  intercept_cr_write; int /*<<< orphan*/  intercept_cr_read; int /*<<< orphan*/  vmcb_msrpm; int /*<<< orphan*/  vmcb; struct vmcb* hsave; } ;
struct vcpu_svm {struct vmcb* vmcb; TYPE_5__ vcpu; TYPE_2__ nested; int /*<<< orphan*/  next_rip; } ;

/* Variables and functions */
 int /*<<< orphan*/  HF_HIF_MASK ; 
 int /*<<< orphan*/  HF_VINTR_MASK ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int SVM_EVTINJ_VALID ; 
 int /*<<< orphan*/  VCPU_REGS_RAX ; 
 int /*<<< orphan*/  VCPU_REGS_RIP ; 
 int /*<<< orphan*/  VCPU_REGS_RSP ; 
 int /*<<< orphan*/  VMCB_CR ; 
 int V_INTR_MASKING_MASK ; 
 int V_IRQ_MASK ; 
 int X86_EFLAGS_IF ; 
 int /*<<< orphan*/  copy_vmcb_control_area (struct vmcb*,struct vmcb*) ; 
 int /*<<< orphan*/  enable_gif (struct vcpu_svm*) ; 
 int /*<<< orphan*/  kvm_clear_exception_queue (TYPE_5__*) ; 
 int /*<<< orphan*/  kvm_clear_interrupt_queue (TYPE_5__*) ; 
 int /*<<< orphan*/  kvm_mmu_reset_context (TYPE_5__*) ; 
 int /*<<< orphan*/  kvm_read_cr0 (TYPE_5__*) ; 
 int /*<<< orphan*/  kvm_register_write (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_cr3 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_all_dirty (struct vmcb*) ; 
 int /*<<< orphan*/  mark_dirty (struct vmcb*,int /*<<< orphan*/ ) ; 
 struct vmcb* nested_svm_map (struct vcpu_svm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_svm_unmap (struct vmcb*,int /*<<< orphan*/ ) ; 
 scalar_t__ npt_enabled ; 
 int /*<<< orphan*/  nsvm_printk (char*,int,...) ; 
 int /*<<< orphan*/  svm_flush_tlb (TYPE_5__*) ; 
 int /*<<< orphan*/  svm_set_cr0 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svm_set_cr4 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svm_set_efer (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nested_svm_vmrun(struct vcpu_svm *svm)
{
	struct vmcb *nested_vmcb;
	struct vmcb *hsave = svm->nested.hsave;
	struct vmcb *vmcb = svm->vmcb;

	nested_vmcb = nested_svm_map(svm, svm->vmcb->save.rax, KM_USER0);
	if (!nested_vmcb)
		return false;

	/* nested_vmcb is our indicator if nested SVM is activated */
	svm->nested.vmcb = svm->vmcb->save.rax;

	/* Clear internal status */
	kvm_clear_exception_queue(&svm->vcpu);
	kvm_clear_interrupt_queue(&svm->vcpu);

	/* Save the old vmcb, so we don't need to pick what we save, but
	   can restore everything when a VMEXIT occurs */
	hsave->save.es     = vmcb->save.es;
	hsave->save.cs     = vmcb->save.cs;
	hsave->save.ss     = vmcb->save.ss;
	hsave->save.ds     = vmcb->save.ds;
	hsave->save.gdtr   = vmcb->save.gdtr;
	hsave->save.idtr   = vmcb->save.idtr;
	hsave->save.efer   = svm->vcpu.arch.shadow_efer;
	hsave->save.cr0    = kvm_read_cr0(&svm->vcpu);
	hsave->save.cr4    = svm->vcpu.arch.cr4;
	hsave->save.rflags = vmcb->save.rflags;
	hsave->save.rip    = svm->next_rip;
	hsave->save.rsp    = vmcb->save.rsp;
	hsave->save.rax    = vmcb->save.rax;
	if (npt_enabled)
		hsave->save.cr3    = vmcb->save.cr3;
	else
		hsave->save.cr3    = svm->vcpu.arch.cr3;

	copy_vmcb_control_area(hsave, vmcb);

	if (svm->vmcb->save.rflags & X86_EFLAGS_IF)
		svm->vcpu.arch.hflags |= HF_HIF_MASK;
	else
		svm->vcpu.arch.hflags &= ~HF_HIF_MASK;

	/* Load the nested guest state */
	svm->vmcb->save.es = nested_vmcb->save.es;
	svm->vmcb->save.cs = nested_vmcb->save.cs;
	svm->vmcb->save.ss = nested_vmcb->save.ss;
	svm->vmcb->save.ds = nested_vmcb->save.ds;
	svm->vmcb->save.gdtr = nested_vmcb->save.gdtr;
	svm->vmcb->save.idtr = nested_vmcb->save.idtr;
	svm->vmcb->save.rflags = nested_vmcb->save.rflags;
	svm_set_efer(&svm->vcpu, nested_vmcb->save.efer);
	svm_set_cr0(&svm->vcpu, nested_vmcb->save.cr0);
	svm_set_cr4(&svm->vcpu, nested_vmcb->save.cr4);
	if (npt_enabled) {
		svm->vmcb->save.cr3 = nested_vmcb->save.cr3;
		svm->vcpu.arch.cr3 = nested_vmcb->save.cr3;
	} else {
		(void)kvm_set_cr3(&svm->vcpu, nested_vmcb->save.cr3);
		kvm_mmu_reset_context(&svm->vcpu);
	}
	mark_dirty(svm->vmcb, VMCB_CR);
	svm->vmcb->save.cr2 = svm->vcpu.arch.cr2 = nested_vmcb->save.cr2;
	kvm_register_write(&svm->vcpu, VCPU_REGS_RAX, nested_vmcb->save.rax);
	kvm_register_write(&svm->vcpu, VCPU_REGS_RSP, nested_vmcb->save.rsp);
	kvm_register_write(&svm->vcpu, VCPU_REGS_RIP, nested_vmcb->save.rip);
	/* In case we don't even reach vcpu_run, the fields are not updated */
	svm->vmcb->save.rax = nested_vmcb->save.rax;
	svm->vmcb->save.rsp = nested_vmcb->save.rsp;
	svm->vmcb->save.rip = nested_vmcb->save.rip;
	svm->vmcb->save.dr7 = nested_vmcb->save.dr7;
	svm->vmcb->save.dr6 = nested_vmcb->save.dr6;
	svm->vmcb->save.cpl = nested_vmcb->save.cpl;

	/* We don't want a nested guest to be more powerful than the guest,
	   so all intercepts are ORed */
	svm->vmcb->control.intercept_cr_read |=
		nested_vmcb->control.intercept_cr_read;
	svm->vmcb->control.intercept_cr_write |=
		nested_vmcb->control.intercept_cr_write;
	svm->vmcb->control.intercept_dr_read |=
		nested_vmcb->control.intercept_dr_read;
	svm->vmcb->control.intercept_dr_write |=
		nested_vmcb->control.intercept_dr_write;
	svm->vmcb->control.intercept_exceptions |=
		nested_vmcb->control.intercept_exceptions;

	svm->vmcb->control.intercept |= nested_vmcb->control.intercept;

	svm->nested.vmcb_msrpm = nested_vmcb->control.msrpm_base_pa;

	/* cache intercepts */
	svm->nested.intercept_cr_read    = nested_vmcb->control.intercept_cr_read;
	svm->nested.intercept_cr_write   = nested_vmcb->control.intercept_cr_write;
	svm->nested.intercept_dr_read    = nested_vmcb->control.intercept_dr_read;
	svm->nested.intercept_dr_write   = nested_vmcb->control.intercept_dr_write;
	svm->nested.intercept_exceptions = nested_vmcb->control.intercept_exceptions;
	svm->nested.intercept            = nested_vmcb->control.intercept;

	svm_flush_tlb(&svm->vcpu);
	svm->vmcb->control.exit_int_info = nested_vmcb->control.exit_int_info;
	svm->vmcb->control.exit_int_info_err = nested_vmcb->control.exit_int_info_err;
	svm->vmcb->control.int_ctl = nested_vmcb->control.int_ctl | V_INTR_MASKING_MASK;
	if (nested_vmcb->control.int_ctl & V_IRQ_MASK) {
		nsvm_printk("nSVM Injecting Interrupt: 0x%x\n",
				nested_vmcb->control.int_ctl);
	}
	if (nested_vmcb->control.int_ctl & V_INTR_MASKING_MASK)
		svm->vcpu.arch.hflags |= HF_VINTR_MASK;
	else
		svm->vcpu.arch.hflags &= ~HF_VINTR_MASK;

	nsvm_printk("nSVM exit_int_info: 0x%x | int_state: 0x%x\n",
			nested_vmcb->control.exit_int_info,
			nested_vmcb->control.int_state);

	svm->vmcb->control.int_vector = nested_vmcb->control.int_vector;
	svm->vmcb->control.int_state = nested_vmcb->control.int_state;
	svm->vmcb->control.tsc_offset += nested_vmcb->control.tsc_offset;
	if (nested_vmcb->control.event_inj & SVM_EVTINJ_VALID)
		nsvm_printk("Injecting Event: 0x%x\n",
				nested_vmcb->control.event_inj);
	svm->vmcb->control.event_inj = nested_vmcb->control.event_inj;
	svm->vmcb->control.event_inj_err = nested_vmcb->control.event_inj_err;

	nested_svm_unmap(nested_vmcb, KM_USER0);

	enable_gif(svm);

	mark_all_dirty(svm->vmcb);

	return true;
}