#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ cr3; scalar_t__ shadow_efer; scalar_t__ cr0; int /*<<< orphan*/  mp_state; int /*<<< orphan*/  cr2; } ;
struct kvm_vcpu {TYPE_3__ arch; int /*<<< orphan*/  kvm; } ;
struct TYPE_10__ {int selector; int base; } ;
struct TYPE_7__ {int /*<<< orphan*/  base; int /*<<< orphan*/  limit; } ;
struct TYPE_6__ {int /*<<< orphan*/  base; int /*<<< orphan*/  limit; } ;
struct kvm_sregs {int cr4; scalar_t__ cr3; scalar_t__ efer; scalar_t__ cr0; TYPE_5__ cs; TYPE_5__ ldt; TYPE_5__ tr; TYPE_5__ ss; TYPE_5__ gs; TYPE_5__ fs; TYPE_5__ es; TYPE_5__ ds; scalar_t__ interrupt_bitmap; int /*<<< orphan*/  apic_base; int /*<<< orphan*/  cr8; int /*<<< orphan*/  cr2; TYPE_2__ gdt; TYPE_1__ idt; } ;
struct descriptor_table {int /*<<< orphan*/  base; int /*<<< orphan*/  limit; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* set_cr4 ) (struct kvm_vcpu*,int) ;int /*<<< orphan*/  (* set_cr0 ) (struct kvm_vcpu*,scalar_t__) ;int /*<<< orphan*/  (* set_efer ) (struct kvm_vcpu*,scalar_t__) ;int /*<<< orphan*/  (* set_gdt ) (struct kvm_vcpu*,struct descriptor_table*) ;int /*<<< orphan*/  (* set_idt ) (struct kvm_vcpu*,struct descriptor_table*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KVM_MP_STATE_RUNNABLE ; 
 int /*<<< orphan*/  VCPU_SREG_CS ; 
 int /*<<< orphan*/  VCPU_SREG_DS ; 
 int /*<<< orphan*/  VCPU_SREG_ES ; 
 int /*<<< orphan*/  VCPU_SREG_FS ; 
 int /*<<< orphan*/  VCPU_SREG_GS ; 
 int /*<<< orphan*/  VCPU_SREG_LDTR ; 
 int /*<<< orphan*/  VCPU_SREG_SS ; 
 int /*<<< orphan*/  VCPU_SREG_TR ; 
 int /*<<< orphan*/  X86_CR0_PE ; 
 int X86_CR4_OSXSAVE ; 
 int find_first_bit (unsigned long const*,int) ; 
 int /*<<< orphan*/  guest_cpuid_has_xsave (struct kvm_vcpu*) ; 
 scalar_t__ irqchip_in_kernel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_long_mode (struct kvm_vcpu*) ; 
 scalar_t__ is_pae (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_reset_context (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_pic_clear_isr_ack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_queue_interrupt (struct kvm_vcpu*,int,int) ; 
 scalar_t__ kvm_read_cr0 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_read_cr0_bits (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvm_read_cr4 (struct kvm_vcpu*) ; 
 int kvm_rip_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_set_apic_base (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_cr8 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_segment (struct kvm_vcpu*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_vcpu_is_bsp (struct kvm_vcpu*) ; 
 TYPE_4__* kvm_x86_ops ; 
 int /*<<< orphan*/  load_pdptrs (struct kvm_vcpu*,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,struct descriptor_table*) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*,struct descriptor_table*) ; 
 int /*<<< orphan*/  stub3 (struct kvm_vcpu*,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (struct kvm_vcpu*,scalar_t__) ; 
 int /*<<< orphan*/  stub5 (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  update_cpuid (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  update_cr8_intercept (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_ioctl_set_sregs(struct kvm_vcpu *vcpu,
				  struct kvm_sregs *sregs)
{
	int mmu_reset_needed = 0;
	int pending_vec, max_bits;
	int ret = 0;
	struct descriptor_table dt;

	vcpu_load(vcpu);

	if (!guest_cpuid_has_xsave(vcpu) && (sregs->cr4 & X86_CR4_OSXSAVE)) {
		ret = -EINVAL;
		goto out;
	}

	dt.limit = sregs->idt.limit;
	dt.base = sregs->idt.base;
	kvm_x86_ops->set_idt(vcpu, &dt);
	dt.limit = sregs->gdt.limit;
	dt.base = sregs->gdt.base;
	kvm_x86_ops->set_gdt(vcpu, &dt);

	vcpu->arch.cr2 = sregs->cr2;
	mmu_reset_needed |= vcpu->arch.cr3 != sregs->cr3;
	vcpu->arch.cr3 = sregs->cr3;

	kvm_set_cr8(vcpu, sregs->cr8);

	mmu_reset_needed |= vcpu->arch.shadow_efer != sregs->efer;
	kvm_x86_ops->set_efer(vcpu, sregs->efer);
	kvm_set_apic_base(vcpu, sregs->apic_base);


	mmu_reset_needed |= kvm_read_cr0(vcpu) != sregs->cr0;
	kvm_x86_ops->set_cr0(vcpu, sregs->cr0);
	vcpu->arch.cr0 = sregs->cr0;

	mmu_reset_needed |= kvm_read_cr4(vcpu) != sregs->cr4;
	kvm_x86_ops->set_cr4(vcpu, sregs->cr4);
	if (sregs->cr4 & X86_CR4_OSXSAVE)
		update_cpuid(vcpu);
	if (!is_long_mode(vcpu) && is_pae(vcpu))
		load_pdptrs(vcpu, vcpu->arch.cr3);

	if (mmu_reset_needed)
		kvm_mmu_reset_context(vcpu);

	max_bits = (sizeof sregs->interrupt_bitmap) << 3;
	pending_vec = find_first_bit(
		(const unsigned long *)sregs->interrupt_bitmap, max_bits);
	if (pending_vec < max_bits) {
		kvm_queue_interrupt(vcpu, pending_vec, false);
		pr_debug("Set back pending irq %d\n", pending_vec);
		if (irqchip_in_kernel(vcpu->kvm))
			kvm_pic_clear_isr_ack(vcpu->kvm);
	}

	kvm_set_segment(vcpu, &sregs->cs, VCPU_SREG_CS);
	kvm_set_segment(vcpu, &sregs->ds, VCPU_SREG_DS);
	kvm_set_segment(vcpu, &sregs->es, VCPU_SREG_ES);
	kvm_set_segment(vcpu, &sregs->fs, VCPU_SREG_FS);
	kvm_set_segment(vcpu, &sregs->gs, VCPU_SREG_GS);
	kvm_set_segment(vcpu, &sregs->ss, VCPU_SREG_SS);

	kvm_set_segment(vcpu, &sregs->tr, VCPU_SREG_TR);
	kvm_set_segment(vcpu, &sregs->ldt, VCPU_SREG_LDTR);

	update_cr8_intercept(vcpu);

	/* Older userspace won't unhalt the vcpu on reset. */
	if (kvm_vcpu_is_bsp(vcpu) && kvm_rip_read(vcpu) == 0xfff0 &&
	    sregs->cs.selector == 0xf000 && sregs->cs.base == 0xffff0000 &&
	    !(kvm_read_cr0_bits(vcpu, X86_CR0_PE)))
		vcpu->arch.mp_state = KVM_MP_STATE_RUNNABLE;

out:
	vcpu_put(vcpu);

	return ret;
}