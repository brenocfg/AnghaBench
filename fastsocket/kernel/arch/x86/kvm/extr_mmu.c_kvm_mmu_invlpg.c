#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  invlpg; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* invlpg ) (struct kvm_vcpu*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ mmu; } ;
struct kvm_vcpu {TYPE_3__ stat; TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  gva_t ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_mmu_flush_tlb (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

void kvm_mmu_invlpg(struct kvm_vcpu *vcpu, gva_t gva)
{
	vcpu->arch.mmu.invlpg(vcpu, gva);
	kvm_mmu_flush_tlb(vcpu);
	++vcpu->stat.invlpg;
}