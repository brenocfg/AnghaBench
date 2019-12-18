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
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  pfn_t ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct page* bad_page ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  gfn_to_pfn (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_is_mmio_pfn (int /*<<< orphan*/ ) ; 
 struct page* pfn_to_page (int /*<<< orphan*/ ) ; 

struct page *gfn_to_page(struct kvm *kvm, gfn_t gfn)
{
	pfn_t pfn;

	pfn = gfn_to_pfn(kvm, gfn);
	if (!kvm_is_mmio_pfn(pfn))
		return pfn_to_page(pfn);

	WARN_ON(kvm_is_mmio_pfn(pfn));

	get_page(bad_page);
	return bad_page;
}