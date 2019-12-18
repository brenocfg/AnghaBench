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
struct vm_area_struct {int vm_flags; unsigned long vm_start; scalar_t__ vm_pgoff; int /*<<< orphan*/  vm_file; } ;
struct mm_struct {int dummy; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned long EINVAL ; 
 scalar_t__ IS_ERR (struct vm_area_struct*) ; 
 unsigned long MAP_FIXED ; 
 unsigned long MAP_SHARED ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PTR_ERR (struct vm_area_struct*) ; 
 unsigned long TASK_SIZE ; 
 int VM_MAYSHARE ; 
 TYPE_1__* current ; 
 unsigned long do_munmap (struct mm_struct*,unsigned long,unsigned long) ; 
 unsigned long get_unmapped_area (int /*<<< orphan*/ ,unsigned long,unsigned long,scalar_t__,unsigned long) ; 
 unsigned long move_vma (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 unsigned long security_file_mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  vm_unacct_memory (unsigned long) ; 
 struct vm_area_struct* vma_to_resize (unsigned long,unsigned long,unsigned long,unsigned long*) ; 

__attribute__((used)) static unsigned long mremap_to(unsigned long addr,
	unsigned long old_len, unsigned long new_addr,
	unsigned long new_len)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma;
	unsigned long ret = -EINVAL;
	unsigned long charged = 0;
	unsigned long map_flags;

	if (new_addr & ~PAGE_MASK)
		goto out;

	if (new_len > TASK_SIZE || new_addr > TASK_SIZE - new_len)
		goto out;

	/* Check if the location we're moving into overlaps the
	 * old location at all, and fail if it does.
	 */
	if ((new_addr <= addr) && (new_addr+new_len) > addr)
		goto out;

	if ((addr <= new_addr) && (addr+old_len) > new_addr)
		goto out;

	ret = security_file_mmap(NULL, 0, 0, 0, new_addr, 1);
	if (ret)
		goto out;

	ret = do_munmap(mm, new_addr, new_len);
	if (ret)
		goto out;

	if (old_len >= new_len) {
		ret = do_munmap(mm, addr+new_len, old_len - new_len);
		if (ret && old_len != new_len)
			goto out;
		old_len = new_len;
	}

	vma = vma_to_resize(addr, old_len, new_len, &charged);
	if (IS_ERR(vma)) {
		ret = PTR_ERR(vma);
		goto out;
	}

	map_flags = MAP_FIXED;
	if (vma->vm_flags & VM_MAYSHARE)
		map_flags |= MAP_SHARED;

	ret = get_unmapped_area(vma->vm_file, new_addr, new_len, vma->vm_pgoff +
				((addr - vma->vm_start) >> PAGE_SHIFT),
				map_flags);
	if (ret & ~PAGE_MASK)
		goto out1;

	ret = move_vma(vma, addr, old_len, new_len, new_addr);
	if (!(ret & ~PAGE_MASK))
		goto out;
out1:
	vm_unacct_memory(charged);

out:
	return ret;
}