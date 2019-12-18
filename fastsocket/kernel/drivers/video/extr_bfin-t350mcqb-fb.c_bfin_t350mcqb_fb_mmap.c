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
struct vm_area_struct {unsigned long vm_start; int vm_flags; scalar_t__ vm_end; } ;
struct TYPE_2__ {scalar_t__ smem_len; } ;
struct fb_info {TYPE_1__ fix; struct bfin_t350mcqbfb_info* par; } ;
struct bfin_t350mcqbfb_info {int lq043_mmap; scalar_t__ fb_buffer; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ ACTIVE_VIDEO_MEM_OFFSET ; 
 int VM_MAYSHARE ; 
 int VM_SHARED ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bfin_t350mcqb_fb_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	struct bfin_t350mcqbfb_info *fbi = info->par;

	if (fbi->lq043_mmap)
		return -1;

	spin_lock(&fbi->lock);
	fbi->lq043_mmap = 1;
	spin_unlock(&fbi->lock);

	vma->vm_start = (unsigned long)(fbi->fb_buffer + ACTIVE_VIDEO_MEM_OFFSET);

	vma->vm_end = vma->vm_start + info->fix.smem_len;
	/* For those who don't understand how mmap works, go read
	 *   Documentation/nommu-mmap.txt.
	 * For those that do, you will know that the VM_MAYSHARE flag
	 * must be set in the vma->vm_flags structure on noMMU
	 *   Other flags can be set, and are documented in
	 *   include/linux/mm.h
	 */
	vma->vm_flags |= VM_MAYSHARE | VM_SHARED;

	return 0;
}