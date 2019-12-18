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
typedef  int /*<<< orphan*/  u64 ;
struct page {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  root_hpa; } ;
struct TYPE_4__ {int mcg_cap; int pv_time_enabled; scalar_t__ pio_data; int /*<<< orphan*/  mce_banks; int /*<<< orphan*/  mp_state; TYPE_1__ mmu; } ;
struct kvm_vcpu {TYPE_2__ arch; struct kvm* kvm; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INVALID_PAGE ; 
 int KVM_MAX_MCE_BANKS ; 
 int /*<<< orphan*/  KVM_MP_STATE_RUNNABLE ; 
 int /*<<< orphan*/  KVM_MP_STATE_UNINITIALIZED ; 
 int __GFP_ZERO ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ irqchip_in_kernel (struct kvm*) ; 
 int kvm_create_lapic (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_free_lapic (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_init_tsc_catchup (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvm_mmu_create (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_destroy (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_pmu_init (struct kvm_vcpu*) ; 
 scalar_t__ kvm_vcpu_is_bsp (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kzalloc (int,int) ; 
 int /*<<< orphan*/  max_tsc_khz ; 
 scalar_t__ page_address (struct page*) ; 

int kvm_arch_vcpu_init(struct kvm_vcpu *vcpu)
{
	struct page *page;
	struct kvm *kvm;
	int r;

	BUG_ON(vcpu->kvm == NULL);
	kvm = vcpu->kvm;

	vcpu->arch.mmu.root_hpa = INVALID_PAGE;
	if (!irqchip_in_kernel(kvm) || kvm_vcpu_is_bsp(vcpu))
		vcpu->arch.mp_state = KVM_MP_STATE_RUNNABLE;
	else
		vcpu->arch.mp_state = KVM_MP_STATE_UNINITIALIZED;

	page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	if (!page) {
		r = -ENOMEM;
		goto fail;
	}
	vcpu->arch.pio_data = page_address(page);

	kvm_init_tsc_catchup(vcpu, max_tsc_khz);

	r = kvm_mmu_create(vcpu);
	if (r < 0)
		goto fail_free_pio_data;

	if (irqchip_in_kernel(kvm)) {
		r = kvm_create_lapic(vcpu);
		if (r < 0)
			goto fail_mmu_destroy;
	}

	vcpu->arch.mce_banks = kzalloc(KVM_MAX_MCE_BANKS * sizeof(u64) * 4,
				       GFP_KERNEL);
	if (!vcpu->arch.mce_banks) {
		r = -ENOMEM;
		goto fail_free_lapic;
	}
	vcpu->arch.mcg_cap = KVM_MAX_MCE_BANKS;

	vcpu->arch.pv_time_enabled = false;
	kvm_pmu_init(vcpu);

	return 0;
fail_free_lapic:
	kvm_free_lapic(vcpu);
fail_mmu_destroy:
	kvm_mmu_destroy(vcpu);
fail_free_pio_data:
	free_page((unsigned long)vcpu->arch.pio_data);
fail:
	return r;
}