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
struct vm_area_struct {int dummy; } ;
struct video_card {int /*<<< orphan*/  mtx; int /*<<< orphan*/  dv_buf; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int dma_region_mmap (int /*<<< orphan*/ *,struct file*,struct vm_area_struct*) ; 
 int do_dv1394_init_default (struct video_card*) ; 
 struct video_card* file_to_video_card (struct file*) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_card_initialized (struct video_card*) ; 

__attribute__((used)) static int dv1394_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct video_card *video = file_to_video_card(file);
	int retval = -EINVAL;

	/*
	 * We cannot use the blocking variant mutex_lock here because .mmap
	 * is called with mmap_sem held, while .ioctl, .read, .write acquire
	 * video->mtx and subsequently call copy_to/from_user which will
	 * grab mmap_sem in case of a page fault.
	 */
	if (!mutex_trylock(&video->mtx))
		return -EAGAIN;

	if ( ! video_card_initialized(video) ) {
		retval = do_dv1394_init_default(video);
		if (retval)
			goto out;
	}

	retval = dma_region_mmap(&video->dv_buf, file, vma);
out:
	mutex_unlock(&video->mtx);
	return retval;
}