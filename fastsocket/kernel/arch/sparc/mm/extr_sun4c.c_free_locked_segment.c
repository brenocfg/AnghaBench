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
struct sun4c_mmu_entry {int dummy; } ;

/* Variables and functions */
 unsigned long SUN4C_REAL_PGDIR_MASK ; 
 int /*<<< orphan*/  add_ring (int /*<<< orphan*/ *,struct sun4c_mmu_entry*) ; 
 int /*<<< orphan*/  flush_user_windows () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  max_user_taken_entries ; 
 struct sun4c_mmu_entry* mmu_entry_pool ; 
 int /*<<< orphan*/  sun4c_flush_segment (unsigned long) ; 
 unsigned char sun4c_get_segmap (unsigned long) ; 
 int /*<<< orphan*/  sun4c_kernel_unmap (struct sun4c_mmu_entry*) ; 
 int /*<<< orphan*/  sun4c_ufree_ring ; 

__attribute__((used)) static void free_locked_segment(unsigned long addr)
{
	struct sun4c_mmu_entry *entry;
	unsigned long flags;
	unsigned char pseg;

	local_irq_save(flags);
	addr &= SUN4C_REAL_PGDIR_MASK;
	pseg = sun4c_get_segmap(addr);
	entry = &mmu_entry_pool[pseg];

	flush_user_windows();
	sun4c_flush_segment(addr);
	sun4c_kernel_unmap(entry);
	add_ring(&sun4c_ufree_ring, entry);
	max_user_taken_entries++;
	local_irq_restore(flags);
}