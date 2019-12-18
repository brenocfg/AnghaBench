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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; } ;
struct vicam_camera {scalar_t__ framebuf; } ;
struct file {struct vicam_camera* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,unsigned long) ; 
 int EAGAIN ; 
 int ENODEV ; 
 int /*<<< orphan*/  PAGE_SHARED ; 
 unsigned long PAGE_SIZE ; 
 scalar_t__ remap_pfn_range (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long vmalloc_to_pfn (void*) ; 

__attribute__((used)) static int
vicam_mmap(struct file *file, struct vm_area_struct *vma)
{
	// TODO: allocate the raw frame buffer if necessary
	unsigned long page, pos;
	unsigned long start = vma->vm_start;
	unsigned long size  = vma->vm_end-vma->vm_start;
	struct vicam_camera *cam = file->private_data;

	if (!cam)
		return -ENODEV;

	DBG("vicam_mmap: %ld\n", size);

	/* We let mmap allocate as much as it wants because Linux was adding 2048 bytes
	 * to the size the application requested for mmap and it was screwing apps up.
	 if (size > VICAM_FRAMES*VICAM_MAX_FRAME_SIZE)
	 return -EINVAL;
	 */

	pos = (unsigned long)cam->framebuf;
	while (size > 0) {
		page = vmalloc_to_pfn((void *)pos);
		if (remap_pfn_range(vma, start, page, PAGE_SIZE, PAGE_SHARED))
			return -EAGAIN;

		start += PAGE_SIZE;
		pos += PAGE_SIZE;
		if (size > PAGE_SIZE)
			size -= PAGE_SIZE;
		else
			size = 0;
	}

	return 0;
}