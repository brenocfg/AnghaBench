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
struct vm_area_struct {unsigned long vm_pgoff; unsigned long vm_end; unsigned long vm_start; } ;
struct TYPE_4__ {unsigned long smem_len; } ;
struct fb_info {TYPE_2__ fix; } ;
struct clcd_fb {TYPE_1__* board; } ;
struct TYPE_3__ {int (* mmap ) (struct clcd_fb*,struct vm_area_struct*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 int stub1 (struct clcd_fb*,struct vm_area_struct*) ; 
 struct clcd_fb* to_clcd (struct fb_info*) ; 

__attribute__((used)) static int clcdfb_mmap(struct fb_info *info,
		       struct vm_area_struct *vma)
{
	struct clcd_fb *fb = to_clcd(info);
	unsigned long len, off = vma->vm_pgoff << PAGE_SHIFT;
	int ret = -EINVAL;

	len = info->fix.smem_len;

	if (off <= len && vma->vm_end - vma->vm_start <= len - off &&
	    fb->board->mmap)
		ret = fb->board->mmap(fb, vma);

	return ret;
}