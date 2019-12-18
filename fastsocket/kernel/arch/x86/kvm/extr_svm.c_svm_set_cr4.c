#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned long cr4; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_5__ {unsigned long cr4; } ;
struct TYPE_8__ {TYPE_1__ save; } ;
struct TYPE_7__ {TYPE_4__* vmcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCB_CR ; 
 unsigned long X86_CR4_MCE ; 
 unsigned long X86_CR4_PAE ; 
 unsigned long X86_CR4_PGE ; 
 int /*<<< orphan*/  mark_dirty (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ npt_enabled ; 
 unsigned long read_cr4 () ; 
 int /*<<< orphan*/  svm_flush_tlb (struct kvm_vcpu*) ; 
 TYPE_3__* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void svm_set_cr4(struct kvm_vcpu *vcpu, unsigned long cr4)
{
	unsigned long host_cr4_mce = read_cr4() & X86_CR4_MCE;
	unsigned long old_cr4 = to_svm(vcpu)->vmcb->save.cr4;

	if (npt_enabled && ((old_cr4 ^ cr4) & X86_CR4_PGE))
		svm_flush_tlb(vcpu);

	vcpu->arch.cr4 = cr4;
	if (!npt_enabled)
		cr4 |= X86_CR4_PAE;
	cr4 |= host_cr4_mce;
	to_svm(vcpu)->vmcb->save.cr4 = cr4;
	mark_dirty(to_svm(vcpu)->vmcb, VMCB_CR);
}