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
struct kvm_memory_slot {int /*<<< orphan*/ * rmap; int /*<<< orphan*/ * dirty_bitmap; scalar_t__ npages; int /*<<< orphan*/ ** lpage_info; } ;

/* Variables and functions */
 int KVM_NR_PAGE_SIZES ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvm_free_physmem_slot(struct kvm_memory_slot *free,
				  struct kvm_memory_slot *dont)
{
	int i;

	if (!dont || free->rmap != dont->rmap)
		vfree(free->rmap);

	if (!dont || free->dirty_bitmap != dont->dirty_bitmap)
		vfree(free->dirty_bitmap);


	for (i = 0; i < KVM_NR_PAGE_SIZES - 1; ++i) {
		if (!dont || free->lpage_info[i] != dont->lpage_info[i]) {
			vfree(free->lpage_info[i]);
			free->lpage_info[i] = NULL;
		}
	}

	free->npages = 0;
	free->dirty_bitmap = NULL;
	free->rmap = NULL;
}