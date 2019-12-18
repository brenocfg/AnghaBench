#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {unsigned long vm_start; unsigned long vm_pgoff; unsigned long vm_end; struct file* vm_file; } ;
struct file {TYPE_2__* f_mapping; } ;
struct TYPE_4__ {TYPE_1__* a_ops; } ;
struct TYPE_3__ {scalar_t__ get_xip_mem; } ;

/* Variables and functions */
 long EBADF ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  force_page_cache_readahead (TYPE_2__*,struct file*,unsigned long,unsigned long) ; 

__attribute__((used)) static long madvise_willneed(struct vm_area_struct * vma,
			     struct vm_area_struct ** prev,
			     unsigned long start, unsigned long end)
{
	struct file *file = vma->vm_file;

	if (!file)
		return -EBADF;

	if (file->f_mapping->a_ops->get_xip_mem) {
		/* no bad return value, but ignore advice */
		return 0;
	}

	*prev = vma;
	start = ((start - vma->vm_start) >> PAGE_SHIFT) + vma->vm_pgoff;
	if (end > vma->vm_end)
		end = vma->vm_end;
	end = ((end - vma->vm_start) >> PAGE_SHIFT) + vma->vm_pgoff;

	force_page_cache_readahead(file->f_mapping, file, start, end - start);
	return 0;
}