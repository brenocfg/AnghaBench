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
struct video_device {int dummy; } ;
struct usb_stv {int maxframesize; int /*<<< orphan*/  lock; scalar_t__ fbuf; int /*<<< orphan*/ * udev; } ;
struct file {struct video_device* private_data; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  PAGE_SHARED ; 
 int PAGE_SIZE ; 
 int STV680_NUMFRAMES ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ remap_pfn_range (struct vm_area_struct*,unsigned long,unsigned long,int,int /*<<< orphan*/ ) ; 
 struct usb_stv* video_get_drvdata (struct video_device*) ; 
 unsigned long vmalloc_to_pfn (void*) ; 

__attribute__((used)) static int stv680_mmap (struct file *file, struct vm_area_struct *vma)
{
	struct video_device *dev = file->private_data;
	struct usb_stv *stv680 = video_get_drvdata(dev);
	unsigned long start = vma->vm_start;
	unsigned long size  = vma->vm_end-vma->vm_start;
	unsigned long page, pos;

	mutex_lock(&stv680->lock);

	if (stv680->udev == NULL) {
		mutex_unlock(&stv680->lock);
		return -EIO;
	}
	if (size > (((STV680_NUMFRAMES * stv680->maxframesize) + PAGE_SIZE - 1)
		    & ~(PAGE_SIZE - 1))) {
		mutex_unlock(&stv680->lock);
		return -EINVAL;
	}
	pos = (unsigned long) stv680->fbuf;
	while (size > 0) {
		page = vmalloc_to_pfn((void *)pos);
		if (remap_pfn_range(vma, start, page, PAGE_SIZE, PAGE_SHARED)) {
			mutex_unlock(&stv680->lock);
			return -EAGAIN;
		}
		start += PAGE_SIZE;
		pos += PAGE_SIZE;
		if (size > PAGE_SIZE)
			size -= PAGE_SIZE;
		else
			size = 0;
	}
	mutex_unlock(&stv680->lock);

	return 0;
}