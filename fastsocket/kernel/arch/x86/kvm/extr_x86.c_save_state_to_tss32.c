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
struct tss_segment_32 {void* ldt_selector; void* gs; void* fs; void* ds; void* ss; void* cs; void* es; void* edi; void* esi; void* ebp; void* esp; void* ebx; void* edx; void* ecx; void* eax; int /*<<< orphan*/  eflags; int /*<<< orphan*/  eip; int /*<<< orphan*/  cr3; } ;
struct TYPE_3__ {int /*<<< orphan*/  cr3; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_rflags ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_REGS_RAX ; 
 int /*<<< orphan*/  VCPU_REGS_RBP ; 
 int /*<<< orphan*/  VCPU_REGS_RBX ; 
 int /*<<< orphan*/  VCPU_REGS_RCX ; 
 int /*<<< orphan*/  VCPU_REGS_RDI ; 
 int /*<<< orphan*/  VCPU_REGS_RDX ; 
 int /*<<< orphan*/  VCPU_REGS_RSI ; 
 int /*<<< orphan*/  VCPU_REGS_RSP ; 
 int /*<<< orphan*/  VCPU_SREG_CS ; 
 int /*<<< orphan*/  VCPU_SREG_DS ; 
 int /*<<< orphan*/  VCPU_SREG_ES ; 
 int /*<<< orphan*/  VCPU_SREG_FS ; 
 int /*<<< orphan*/  VCPU_SREG_GS ; 
 int /*<<< orphan*/  VCPU_SREG_LDTR ; 
 int /*<<< orphan*/  VCPU_SREG_SS ; 
 void* get_segment_selector (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 void* kvm_register_read (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_rip_read (struct kvm_vcpu*) ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 

__attribute__((used)) static void save_state_to_tss32(struct kvm_vcpu *vcpu,
				struct tss_segment_32 *tss)
{
	tss->cr3 = vcpu->arch.cr3;
	tss->eip = kvm_rip_read(vcpu);
	tss->eflags = kvm_x86_ops->get_rflags(vcpu);
	tss->eax = kvm_register_read(vcpu, VCPU_REGS_RAX);
	tss->ecx = kvm_register_read(vcpu, VCPU_REGS_RCX);
	tss->edx = kvm_register_read(vcpu, VCPU_REGS_RDX);
	tss->ebx = kvm_register_read(vcpu, VCPU_REGS_RBX);
	tss->esp = kvm_register_read(vcpu, VCPU_REGS_RSP);
	tss->ebp = kvm_register_read(vcpu, VCPU_REGS_RBP);
	tss->esi = kvm_register_read(vcpu, VCPU_REGS_RSI);
	tss->edi = kvm_register_read(vcpu, VCPU_REGS_RDI);
	tss->es = get_segment_selector(vcpu, VCPU_SREG_ES);
	tss->cs = get_segment_selector(vcpu, VCPU_SREG_CS);
	tss->ss = get_segment_selector(vcpu, VCPU_SREG_SS);
	tss->ds = get_segment_selector(vcpu, VCPU_SREG_DS);
	tss->fs = get_segment_selector(vcpu, VCPU_SREG_FS);
	tss->gs = get_segment_selector(vcpu, VCPU_SREG_GS);
	tss->ldt_selector = get_segment_selector(vcpu, VCPU_SREG_LDTR);
}