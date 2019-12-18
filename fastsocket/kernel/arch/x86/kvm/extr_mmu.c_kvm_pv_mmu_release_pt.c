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
struct kvm_vcpu {TYPE_1__* kvm; } ;
typedef  int gpa_t ;
struct TYPE_2__ {int /*<<< orphan*/  mmu_lock; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  mmu_unshadow (TYPE_1__*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvm_pv_mmu_release_pt(struct kvm_vcpu *vcpu, gpa_t addr)
{
	spin_lock(&vcpu->kvm->mmu_lock);
	mmu_unshadow(vcpu->kvm, addr >> PAGE_SHIFT);
	spin_unlock(&vcpu->kvm->mmu_lock);
	return 1;
}