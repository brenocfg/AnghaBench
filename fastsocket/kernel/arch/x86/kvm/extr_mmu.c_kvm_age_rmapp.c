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
typedef  int u64 ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,unsigned long*) ; 
 scalar_t__ ffs (int) ; 
 int /*<<< orphan*/  is_shadow_present_pte (int) ; 
 int kvm_unmap_rmapp (struct kvm*,unsigned long*,unsigned long) ; 
 int* rmap_next (struct kvm*,unsigned long*,int*) ; 
 int shadow_accessed_mask ; 

__attribute__((used)) static int kvm_age_rmapp(struct kvm *kvm, unsigned long *rmapp,
			 unsigned long data)
{
	u64 *spte;
	int young = 0;

	/*
	 * In case of absence of EPT Access and Dirty Bits supports,
	 * emulate the accessed bit for EPT, by checking if this page has
	 * an EPT mapping, and clearing it if it does. On the next access,
	 * a new EPT mapping will be established.
	 * This has some overhead, but not as much as the cost of swapping
	 * out actively used pages or breaking up actively used hugepages.
	 */
	if (!shadow_accessed_mask)
		return kvm_unmap_rmapp(kvm, rmapp, data);

	spte = rmap_next(kvm, rmapp, NULL);
	while (spte) {
		int _young;
		u64 _spte = *spte;
		BUG_ON(!is_shadow_present_pte(_spte));
		_young = _spte & shadow_accessed_mask;
		if (_young) {
			young = 1;
			clear_bit((ffs(shadow_accessed_mask) - 1),
				 (unsigned long *)spte);
		}
		spte = rmap_next(kvm, rmapp, spte);
	}
	return young;
}