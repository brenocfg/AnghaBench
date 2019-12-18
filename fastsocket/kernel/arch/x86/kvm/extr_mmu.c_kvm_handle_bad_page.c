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
 int EFAULT ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  gfn_to_hva (struct kvm*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_fault_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ is_hwpoison_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_release_pfn_clean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_send_hwpoison_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_handle_bad_page(struct kvm *kvm, gfn_t gfn, pfn_t pfn)
{
	kvm_release_pfn_clean(pfn);
	if (is_hwpoison_pfn(pfn)) {
		kvm_send_hwpoison_signal(gfn_to_hva(kvm, gfn), current);
		return 0;
	} else if (is_fault_pfn(pfn))
		return -EFAULT;

	return 1;
}