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
struct mmu_page_path {unsigned int* idx; struct kvm_mmu_page** parent; } ;
struct kvm_mmu_page {int /*<<< orphan*/  unsync_child_bitmap; scalar_t__ unsync_children; } ;

/* Variables and functions */
 int PT64_ROOT_LEVEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmu_pages_clear_parents(struct mmu_page_path *parents)
{
	struct kvm_mmu_page *sp;
	unsigned int level = 0;

	do {
		unsigned int idx = parents->idx[level];

		sp = parents->parent[level];
		if (!sp)
			return;

		--sp->unsync_children;
		WARN_ON((int)sp->unsync_children < 0);
		__clear_bit(idx, sp->unsync_child_bitmap);
		level++;
	} while (level < PT64_ROOT_LEVEL-1 && !sp->unsync_children);
}