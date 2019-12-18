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
struct TYPE_4__ {int apic_base; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {void* msrpm; void* hsave; } ;
struct vcpu_svm {int vmcb_pa; struct kvm_vcpu vcpu; scalar_t__ asid_generation; void* vmcb; TYPE_1__ nested; void* msrpm; int /*<<< orphan*/  tsc_ratio; } ;
struct page {int dummy; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct kvm_vcpu* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSRPM_ALLOC_ORDER ; 
 int MSR_IA32_APICBASE_BSP ; 
 int MSR_IA32_APICBASE_ENABLE ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  TSC_RATIO_DEFAULT ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_page (void*) ; 
 int /*<<< orphan*/  fx_init (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  init_vmcb (struct vcpu_svm*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct vcpu_svm*) ; 
 struct vcpu_svm* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_cache ; 
 int kvm_vcpu_init (struct kvm_vcpu*,struct kvm*,unsigned int) ; 
 scalar_t__ kvm_vcpu_is_bsp (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_uninit (struct kvm_vcpu*) ; 
 void* page_address (struct page*) ; 
 int page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  svm_vcpu_init_msrpm (void*) ; 

__attribute__((used)) static struct kvm_vcpu *svm_create_vcpu(struct kvm *kvm, unsigned int id)
{
	struct vcpu_svm *svm;
	struct page *page;
	struct page *msrpm_pages;
	struct page *hsave_page;
	struct page *nested_msrpm_pages;
	int err;

	svm = kmem_cache_zalloc(kvm_vcpu_cache, GFP_KERNEL);
	if (!svm) {
		err = -ENOMEM;
		goto out;
	}

	svm->tsc_ratio = TSC_RATIO_DEFAULT;

	err = kvm_vcpu_init(&svm->vcpu, kvm, id);
	if (err)
		goto free_svm;

	err = -ENOMEM;
	page = alloc_page(GFP_KERNEL);
	if (!page)
		goto uninit;

	msrpm_pages = alloc_pages(GFP_KERNEL, MSRPM_ALLOC_ORDER);
	if (!msrpm_pages)
		goto free_page1;

	nested_msrpm_pages = alloc_pages(GFP_KERNEL, MSRPM_ALLOC_ORDER);
	if (!nested_msrpm_pages)
		goto free_page2;

	hsave_page = alloc_page(GFP_KERNEL);
	if (!hsave_page)
		goto free_page3;

	svm->nested.hsave = page_address(hsave_page);

	svm->msrpm = page_address(msrpm_pages);
	svm_vcpu_init_msrpm(svm->msrpm);

	svm->nested.msrpm = page_address(nested_msrpm_pages);

	svm->vmcb = page_address(page);
	clear_page(svm->vmcb);
	svm->vmcb_pa = page_to_pfn(page) << PAGE_SHIFT;
	svm->asid_generation = 0;
	init_vmcb(svm);

	fx_init(&svm->vcpu);
	svm->vcpu.arch.apic_base = 0xfee00000 | MSR_IA32_APICBASE_ENABLE;
	if (kvm_vcpu_is_bsp(&svm->vcpu))
		svm->vcpu.arch.apic_base |= MSR_IA32_APICBASE_BSP;

	return &svm->vcpu;

free_page3:
	__free_pages(nested_msrpm_pages, MSRPM_ALLOC_ORDER);
free_page2:
	__free_pages(msrpm_pages, MSRPM_ALLOC_ORDER);
free_page1:
	__free_page(page);
uninit:
	kvm_vcpu_uninit(&svm->vcpu);
free_svm:
	kmem_cache_free(kvm_vcpu_cache, svm);
out:
	return ERR_PTR(err);
}