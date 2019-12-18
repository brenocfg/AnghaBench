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
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int install_file_pte (struct mm_struct*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int populate_range(struct mm_struct *mm, struct vm_area_struct *vma,
			unsigned long addr, unsigned long size, pgoff_t pgoff)
{
	int err;

	do {
		err = install_file_pte(mm, vma, addr, pgoff, vma->vm_page_prot);
		if (err)
			return err;

		size -= PAGE_SIZE;
		addr += PAGE_SIZE;
		pgoff++;
	} while (size);

        return 0;

}