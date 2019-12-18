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
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  kvm; } ;
struct vcpu_svm {TYPE_1__ vcpu; } ;
struct page {int dummy; } ;
typedef  enum km_type { ____Placeholder_km_type } km_type ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 struct page* gfn_to_page (int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_error_page (struct page*) ; 
 void* kmap_atomic (struct page*,int) ; 
 int /*<<< orphan*/  kvm_inject_gp (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_release_page_clean (struct page*) ; 

__attribute__((used)) static void *nested_svm_map(struct vcpu_svm *svm, u64 gpa, enum km_type idx)
{
	struct page *page;

	page = gfn_to_page(svm->vcpu.kvm, gpa >> PAGE_SHIFT);
	if (is_error_page(page))
		goto error;

	return kmap_atomic(page, idx);

error:
	kvm_release_page_clean(page);
	kvm_inject_gp(&svm->vcpu, 0);

	return NULL;
}