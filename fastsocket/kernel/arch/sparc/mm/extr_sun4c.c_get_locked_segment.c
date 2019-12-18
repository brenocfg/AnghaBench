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
struct sun4c_mmu_entry {unsigned long vaddr; } ;

/* Variables and functions */
 unsigned long SUN4C_REAL_PGDIR_MASK ; 
 int /*<<< orphan*/  flush_user_windows () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  max_user_taken_entries ; 
 int /*<<< orphan*/  sun4c_kernel_map (struct sun4c_mmu_entry*) ; 
 struct sun4c_mmu_entry* sun4c_user_strategy () ; 

__attribute__((used)) static void get_locked_segment(unsigned long addr)
{
	struct sun4c_mmu_entry *stolen;
	unsigned long flags;

	local_irq_save(flags);
	addr &= SUN4C_REAL_PGDIR_MASK;
	stolen = sun4c_user_strategy();
	max_user_taken_entries--;
	stolen->vaddr = addr;
	flush_user_windows();
	sun4c_kernel_map(stolen);
	local_irq_restore(flags);
}