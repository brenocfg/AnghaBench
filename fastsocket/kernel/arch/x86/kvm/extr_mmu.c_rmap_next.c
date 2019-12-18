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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_rmap_desc {struct kvm_rmap_desc* more; int /*<<< orphan*/ ** sptes; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int RMAP_EXT ; 

__attribute__((used)) static u64 *rmap_next(struct kvm *kvm, unsigned long *rmapp, u64 *spte)
{
	struct kvm_rmap_desc *desc;
	struct kvm_rmap_desc *prev_desc;
	u64 *prev_spte;
	int i;

	if (!*rmapp)
		return NULL;
	else if (!(*rmapp & 1)) {
		if (!spte)
			return (u64 *)*rmapp;
		return NULL;
	}
	desc = (struct kvm_rmap_desc *)(*rmapp & ~1ul);
	prev_desc = NULL;
	prev_spte = NULL;
	while (desc) {
		for (i = 0; i < RMAP_EXT && desc->sptes[i]; ++i) {
			if (prev_spte == spte)
				return desc->sptes[i];
			prev_spte = desc->sptes[i];
		}
		desc = desc->more;
	}
	return NULL;
}