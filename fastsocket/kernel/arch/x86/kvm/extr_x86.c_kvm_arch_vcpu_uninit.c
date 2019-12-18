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
struct TYPE_4__ {scalar_t__ pio_data; int /*<<< orphan*/  mce_banks; } ;
struct kvm_vcpu {TYPE_2__ arch; TYPE_1__* kvm; } ;
struct TYPE_3__ {int /*<<< orphan*/  srcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_free_lapic (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_destroy (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_pmu_destroy (struct kvm_vcpu*) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 

void kvm_arch_vcpu_uninit(struct kvm_vcpu *vcpu)
{
	int idx;

	kvm_pmu_destroy(vcpu);
	kfree(vcpu->arch.mce_banks);
	kvm_free_lapic(vcpu);
	idx = srcu_read_lock(&vcpu->kvm->srcu);
	kvm_mmu_destroy(vcpu);
	srcu_read_unlock(&vcpu->kvm->srcu, idx);
	free_page((unsigned long)vcpu->arch.pio_data);
}