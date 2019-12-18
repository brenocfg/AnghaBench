#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct page {int dummy; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
typedef  int /*<<< orphan*/  gva_t ;
typedef  int gpa_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int UNMAPPED_GVA ; 
 struct page* gfn_to_page (int /*<<< orphan*/ ,int) ; 
 int kvm_mmu_gva_to_gpa_read (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct page *gva_to_page(struct kvm_vcpu *vcpu, gva_t gva)
{
	struct page *page;

	gpa_t gpa = kvm_mmu_gva_to_gpa_read(vcpu, gva, NULL);

	if (gpa == UNMAPPED_GVA)
		return NULL;

	page = gfn_to_page(vcpu->kvm, gpa >> PAGE_SHIFT);

	return page;
}