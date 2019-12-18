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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; unsigned long vm_pgoff; } ;
struct camera_data {unsigned long frame_size; unsigned long num_frames; int mmapped; int /*<<< orphan*/  busy_lock; scalar_t__ frame_buffer; int /*<<< orphan*/  present; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,unsigned long,unsigned long) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENODEV ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  PAGE_SHARED ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 unsigned long kvirt_to_pa (unsigned long) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ remap_pfn_range (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 

int cpia2_remap_buffer(struct camera_data *cam, struct vm_area_struct *vma)
{
	const char *adr = (const char *)vma->vm_start;
	unsigned long size = vma->vm_end-vma->vm_start;
	unsigned long start_offset = vma->vm_pgoff << PAGE_SHIFT;
	unsigned long start = (unsigned long) adr;
	unsigned long page, pos;

	if (!cam)
		return -ENODEV;

	DBG("mmap offset:%ld size:%ld\n", start_offset, size);

	/* make this _really_ smp-safe */
	if (mutex_lock_interruptible(&cam->busy_lock))
		return -ERESTARTSYS;

	if (!cam->present) {
		mutex_unlock(&cam->busy_lock);
		return -ENODEV;
	}

	if (size > cam->frame_size*cam->num_frames  ||
	    (start_offset % cam->frame_size) != 0 ||
	    (start_offset+size > cam->frame_size*cam->num_frames)) {
		mutex_unlock(&cam->busy_lock);
		return -EINVAL;
	}

	pos = ((unsigned long) (cam->frame_buffer)) + start_offset;
	while (size > 0) {
		page = kvirt_to_pa(pos);
		if (remap_pfn_range(vma, start, page >> PAGE_SHIFT, PAGE_SIZE, PAGE_SHARED)) {
			mutex_unlock(&cam->busy_lock);
			return -EAGAIN;
		}
		start += PAGE_SIZE;
		pos += PAGE_SIZE;
		if (size > PAGE_SIZE)
			size -= PAGE_SIZE;
		else
			size = 0;
	}

	cam->mmapped = true;
	mutex_unlock(&cam->busy_lock);
	return 0;
}