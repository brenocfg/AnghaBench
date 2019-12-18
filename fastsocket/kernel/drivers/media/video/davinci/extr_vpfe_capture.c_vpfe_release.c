#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vpfe_subdev_info {int /*<<< orphan*/  grp_id; } ;
struct vpfe_fh {int /*<<< orphan*/  prio; scalar_t__ io_allowed; } ;
struct vpfe_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  pdev; scalar_t__ initialized; int /*<<< orphan*/  usrs; int /*<<< orphan*/  prio; int /*<<< orphan*/  numbuffers; scalar_t__ io_usrs; int /*<<< orphan*/  buffer_queue; int /*<<< orphan*/  v4l2_dev; struct vpfe_subdev_info* current_subdev; scalar_t__ started; } ;
struct file {struct vpfe_fh* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* close ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  owner; TYPE_1__ hw_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  numbuffers; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 TYPE_3__* ccdc_dev ; 
 TYPE_2__ config_params ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  kfree (struct vpfe_fh*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int v4l2_device_call_until_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_prio_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video ; 
 struct vpfe_device* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  videobuf_streamoff (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpfe_detach_irq (struct vpfe_device*) ; 
 int /*<<< orphan*/  vpfe_stop_ccdc_capture (struct vpfe_device*) ; 

__attribute__((used)) static int vpfe_release(struct file *file)
{
	struct vpfe_device *vpfe_dev = video_drvdata(file);
	struct vpfe_fh *fh = file->private_data;
	struct vpfe_subdev_info *sdinfo;
	int ret;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_release\n");

	/* Get the device lock */
	mutex_lock(&vpfe_dev->lock);
	/* if this instance is doing IO */
	if (fh->io_allowed) {
		if (vpfe_dev->started) {
			sdinfo = vpfe_dev->current_subdev;
			ret = v4l2_device_call_until_err(&vpfe_dev->v4l2_dev,
							 sdinfo->grp_id,
							 video, s_stream, 0);
			if (ret && (ret != -ENOIOCTLCMD))
				v4l2_err(&vpfe_dev->v4l2_dev,
				"stream off failed in subdev\n");
			vpfe_stop_ccdc_capture(vpfe_dev);
			vpfe_detach_irq(vpfe_dev);
			videobuf_streamoff(&vpfe_dev->buffer_queue);
		}
		vpfe_dev->io_usrs = 0;
		vpfe_dev->numbuffers = config_params.numbuffers;
	}

	/* Decrement device usrs counter */
	vpfe_dev->usrs--;
	/* Close the priority */
	v4l2_prio_close(&vpfe_dev->prio, &fh->prio);
	/* If this is the last file handle */
	if (!vpfe_dev->usrs) {
		vpfe_dev->initialized = 0;
		if (ccdc_dev->hw_ops.close)
			ccdc_dev->hw_ops.close(vpfe_dev->pdev);
		module_put(ccdc_dev->owner);
	}
	mutex_unlock(&vpfe_dev->lock);
	file->private_data = NULL;
	/* Free memory allocated to file handle object */
	kfree(fh);
	return 0;
}