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
struct file {struct cpia2_fh* private_data; } ;
struct cpia2_fh {scalar_t__ mmapped; int /*<<< orphan*/  prio; } ;
struct camera_data {scalar_t__ open_count; int /*<<< orphan*/  busy_lock; int /*<<< orphan*/  prio; scalar_t__ COM_len; scalar_t__ APP_len; int /*<<< orphan*/  present; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  V4L2_PRIORITY_UNSET ; 
 scalar_t__ cpia2_allocate_buffers (struct camera_data*) ; 
 int /*<<< orphan*/  cpia2_dbg_dump_registers (struct camera_data*) ; 
 scalar_t__ cpia2_reset_camera (struct camera_data*) ; 
 struct cpia2_fh* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_prio_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct camera_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int cpia2_open(struct file *file)
{
	struct camera_data *cam = video_drvdata(file);
	int retval = 0;

	if (!cam) {
		ERR("Internal error, camera_data not found!\n");
		return -ENODEV;
	}

	if(mutex_lock_interruptible(&cam->busy_lock))
		return -ERESTARTSYS;

	if(!cam->present) {
		retval = -ENODEV;
		goto err_return;
	}

	if (cam->open_count > 0) {
		goto skip_init;
	}

	if (cpia2_allocate_buffers(cam)) {
		retval = -ENOMEM;
		goto err_return;
	}

	/* reset the camera */
	if (cpia2_reset_camera(cam) < 0) {
		retval = -EIO;
		goto err_return;
	}

	cam->APP_len = 0;
	cam->COM_len = 0;

skip_init:
	{
		struct cpia2_fh *fh = kmalloc(sizeof(*fh),GFP_KERNEL);
		if(!fh) {
			retval = -ENOMEM;
			goto err_return;
		}
		file->private_data = fh;
		fh->prio = V4L2_PRIORITY_UNSET;
		v4l2_prio_open(&cam->prio, &fh->prio);
		fh->mmapped = 0;
	}

	++cam->open_count;

	cpia2_dbg_dump_registers(cam);

err_return:
	mutex_unlock(&cam->busy_lock);
	return retval;
}