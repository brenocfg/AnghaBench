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
struct kvm_rmap_desc {scalar_t__ more; int /*<<< orphan*/ ** sptes; } ;

/* Variables and functions */
 int RMAP_EXT ; 
 int /*<<< orphan*/  mmu_free_rmap_desc (struct kvm_rmap_desc*) ; 

__attribute__((used)) static void rmap_desc_remove_entry(unsigned long *rmapp,
				   struct kvm_rmap_desc *desc,
				   int i,
				   struct kvm_rmap_desc *prev_desc)
{
	int j;

	for (j = RMAP_EXT - 1; !desc->sptes[j] && j > i; --j)
		;
	desc->sptes[i] = desc->sptes[j];
	desc->sptes[j] = NULL;
	if (j != 0)
		return;
	if (!prev_desc && !desc->more)
		*rmapp = (unsigned long)desc->sptes[0];
	else
		if (prev_desc)
			prev_desc->more = desc->more;
		else
			*rmapp = (unsigned long)desc->more | 1;
	mmu_free_rmap_desc(desc);
}