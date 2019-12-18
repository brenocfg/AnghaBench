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
struct vpif_params {int dummy; } ;
struct vpif_fh {int initialized; int /*<<< orphan*/  prio; scalar_t__* io_allowed; struct channel_obj* channel; } ;
struct vpif_capture_config {int subdev_count; int /*<<< orphan*/ * subdev_info; } ;
struct video_obj {scalar_t__ input_idx; } ;
struct video_device {int dummy; } ;
struct file {struct vpif_fh* private_data; } ;
struct common_obj {int /*<<< orphan*/  lock; } ;
struct channel_obj {int initialized; int /*<<< orphan*/  prio; int /*<<< orphan*/  usrs; int /*<<< orphan*/  vpifparams; int /*<<< orphan*/ * curr_subdev_info; struct common_obj* common; struct video_obj video; } ;
struct TYPE_4__ {struct vpif_capture_config* platform_data; } ;
struct TYPE_3__ {scalar_t__* sd; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  V4L2_PRIORITY_UNSET ; 
 size_t VPIF_VIDEO_INDEX ; 
 int /*<<< orphan*/  debug ; 
 struct vpif_fh* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_prio_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct channel_obj* video_get_drvdata (struct video_device*) ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* vpif_dev ; 
 int /*<<< orphan*/  vpif_err (char*) ; 
 TYPE_1__ vpif_obj ; 

__attribute__((used)) static int vpif_open(struct file *filep)
{
	struct vpif_capture_config *config = vpif_dev->platform_data;
	struct video_device *vdev = video_devdata(filep);
	struct common_obj *common;
	struct video_obj *vid_ch;
	struct channel_obj *ch;
	struct vpif_fh *fh;
	int i, ret = 0;

	vpif_dbg(2, debug, "vpif_open\n");

	ch = video_get_drvdata(vdev);

	vid_ch = &ch->video;
	common = &ch->common[VPIF_VIDEO_INDEX];

	if (mutex_lock_interruptible(&common->lock))
		return -ERESTARTSYS;

	if (NULL == ch->curr_subdev_info) {
		/**
		 * search through the sub device to see a registered
		 * sub device and make it as current sub device
		 */
		for (i = 0; i < config->subdev_count; i++) {
			if (vpif_obj.sd[i]) {
				/* the sub device is registered */
				ch->curr_subdev_info = &config->subdev_info[i];
				/* make first input as the current input */
				vid_ch->input_idx = 0;
				break;
			}
		}
		if (i == config->subdev_count) {
			vpif_err("No sub device registered\n");
			ret = -ENOENT;
			goto exit;
		}
	}

	/* Allocate memory for the file handle object */
	fh = kmalloc(sizeof(struct vpif_fh), GFP_KERNEL);
	if (NULL == fh) {
		vpif_err("unable to allocate memory for file handle object\n");
		ret = -ENOMEM;
		goto exit;
	}

	/* store pointer to fh in private_data member of filep */
	filep->private_data = fh;
	fh->channel = ch;
	fh->initialized = 0;
	/* If decoder is not initialized. initialize it */
	if (!ch->initialized) {
		fh->initialized = 1;
		ch->initialized = 1;
		memset(&(ch->vpifparams), 0, sizeof(struct vpif_params));
	}
	/* Increment channel usrs counter */
	ch->usrs++;
	/* Set io_allowed member to false */
	fh->io_allowed[VPIF_VIDEO_INDEX] = 0;
	/* Initialize priority of this instance to default priority */
	fh->prio = V4L2_PRIORITY_UNSET;
	v4l2_prio_open(&ch->prio, &fh->prio);
exit:
	mutex_unlock(&common->lock);
	return ret;
}