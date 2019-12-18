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
struct hstate {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 unsigned long EINVAL ; 
 struct hstate* hstate_file (struct file*) ; 
 int /*<<< orphan*/  huge_page_shift (struct hstate*) ; 
 int /*<<< orphan*/ * mmu_huge_psizes ; 
 int shift_to_mmu_psize (int /*<<< orphan*/ ) ; 
 unsigned long slice_get_unmapped_area (unsigned long,unsigned long,unsigned long,int,int,int /*<<< orphan*/ ) ; 

unsigned long hugetlb_get_unmapped_area(struct file *file, unsigned long addr,
					unsigned long len, unsigned long pgoff,
					unsigned long flags)
{
	struct hstate *hstate = hstate_file(file);
	int mmu_psize = shift_to_mmu_psize(huge_page_shift(hstate));

	if (!mmu_huge_psizes[mmu_psize])
		return -EINVAL;
	return slice_get_unmapped_area(addr, len, flags, mmu_psize, 1, 0);
}