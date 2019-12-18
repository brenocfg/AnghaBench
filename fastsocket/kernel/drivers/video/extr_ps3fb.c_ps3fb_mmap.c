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
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; unsigned long vm_pgoff; int /*<<< orphan*/  vm_page_prot; } ;
struct TYPE_2__ {unsigned long smem_len; scalar_t__ smem_start; } ;
struct fb_info {int /*<<< orphan*/  device; TYPE_1__ fix; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 scalar_t__ remap_pfn_range (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ps3fb_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	unsigned long size, offset;

	size = vma->vm_end - vma->vm_start;
	offset = vma->vm_pgoff << PAGE_SHIFT;
	if (offset + size > info->fix.smem_len)
		return -EINVAL;

	offset += info->fix.smem_start;
	if (remap_pfn_range(vma, vma->vm_start, offset >> PAGE_SHIFT,
			    size, vma->vm_page_prot))
		return -EAGAIN;

	dev_dbg(info->device, "ps3fb: mmap framebuffer P(%lx)->V(%lx)\n",
		offset, vma->vm_start);
	return 0;
}