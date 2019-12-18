#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {int /*<<< orphan*/  unmap_area; scalar_t__ shlib_base; int /*<<< orphan*/  get_unmapped_exec_area; int /*<<< orphan*/  get_unmapped_area; int /*<<< orphan*/  mmap_base; } ;
struct TYPE_2__ {int personality; } ;

/* Variables and functions */
 int READ_IMPLIES_EXEC ; 
 scalar_t__ SHLIB_BASE ; 
 int /*<<< orphan*/  arch_get_unmapped_area ; 
 int /*<<< orphan*/  arch_get_unmapped_area_topdown ; 
 int /*<<< orphan*/  arch_get_unmapped_exec_area ; 
 int /*<<< orphan*/  arch_unmap_area ; 
 int /*<<< orphan*/  arch_unmap_area_topdown ; 
 TYPE_1__* current ; 
 int exec_shield ; 
 int /*<<< orphan*/  mmap_base () ; 
 scalar_t__ mmap_is_ia32 () ; 
 scalar_t__ mmap_is_legacy () ; 
 int /*<<< orphan*/  mmap_legacy_base () ; 
 scalar_t__ mmap_rnd () ; 

void arch_pick_mmap_layout(struct mm_struct *mm)
{
	if (!(2 & exec_shield) && mmap_is_legacy()) {
		mm->mmap_base = mmap_legacy_base();
		mm->get_unmapped_area = arch_get_unmapped_area;
		mm->unmap_area = arch_unmap_area;
	} else {
		mm->mmap_base = mmap_base();
		mm->get_unmapped_area = arch_get_unmapped_area_topdown;
		if (!(current->personality & READ_IMPLIES_EXEC)
		    && mmap_is_ia32()) {
			mm->get_unmapped_exec_area = arch_get_unmapped_exec_area;
			mm->shlib_base = SHLIB_BASE + mmap_rnd();
		}
		mm->unmap_area = arch_unmap_area_topdown;
	}
}