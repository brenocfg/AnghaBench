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
struct vm_area_struct {int /*<<< orphan*/  vm_start; int /*<<< orphan*/  vm_mm; } ;

/* Variables and functions */
 unsigned int get_slice_psize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long mmu_psize_to_shift (unsigned int) ; 

unsigned long vma_mmu_pagesize(struct vm_area_struct *vma)
{
	unsigned int psize = get_slice_psize(vma->vm_mm, vma->vm_start);

	return 1UL << mmu_psize_to_shift(psize);
}