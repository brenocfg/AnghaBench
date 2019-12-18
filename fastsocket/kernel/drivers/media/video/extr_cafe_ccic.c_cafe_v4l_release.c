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
struct file {struct cafe_camera* private_data; } ;
struct cafe_camera {scalar_t__ users; int /*<<< orphan*/  s_mutex; struct file* owner; } ;

/* Variables and functions */
 scalar_t__ alloc_bufs_at_read ; 
 int /*<<< orphan*/  cafe_ctlr_power_down (struct cafe_camera*) ; 
 int /*<<< orphan*/  cafe_ctlr_stop_dma (struct cafe_camera*) ; 
 int /*<<< orphan*/  cafe_free_dma_bufs (struct cafe_camera*) ; 
 int /*<<< orphan*/  cafe_free_sio_buffers (struct cafe_camera*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cafe_v4l_release(struct file *filp)
{
	struct cafe_camera *cam = filp->private_data;

	mutex_lock(&cam->s_mutex);
	(cam->users)--;
	if (filp == cam->owner) {
		cafe_ctlr_stop_dma(cam);
		cafe_free_sio_buffers(cam);
		cam->owner = NULL;
	}
	if (cam->users == 0) {
		cafe_ctlr_power_down(cam);
		if (alloc_bufs_at_read)
			cafe_free_dma_bufs(cam);
	}
	mutex_unlock(&cam->s_mutex);
	return 0;
}