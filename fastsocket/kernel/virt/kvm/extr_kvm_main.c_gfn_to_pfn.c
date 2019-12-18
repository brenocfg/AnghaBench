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
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  pfn_t ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  bad_page ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 unsigned long gfn_to_hva (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hva_to_pfn (struct kvm*,unsigned long) ; 
 scalar_t__ kvm_is_error_hva (unsigned long) ; 
 int /*<<< orphan*/  page_to_pfn (int /*<<< orphan*/ ) ; 

pfn_t gfn_to_pfn(struct kvm *kvm, gfn_t gfn)
{
	unsigned long addr;

	addr = gfn_to_hva(kvm, gfn);
	if (kvm_is_error_hva(addr)) {
		get_page(bad_page);
		return page_to_pfn(bad_page);
	}

	return hva_to_pfn(kvm, addr);
}