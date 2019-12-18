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
struct vpif_fh {int /*<<< orphan*/ * io_allowed; struct channel_obj* channel; } ;
struct file {int dummy; } ;
struct common_obj {int started; int /*<<< orphan*/  buffer_queue; int /*<<< orphan*/  lock; } ;
struct channel_obj {scalar_t__ channel_id; struct common_obj* common; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int ERESTARTSYS ; 
 int V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 scalar_t__ VPIF_CHANNEL2_VIDEO ; 
 scalar_t__ VPIF_CHANNEL3_VIDEO ; 
 size_t VPIF_VIDEO_INDEX ; 
 int /*<<< orphan*/  channel2_intr_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel3_intr_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_channel2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_channel3 (int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int videobuf_streamoff (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpif_err (char*) ; 

__attribute__((used)) static int vpif_streamoff(struct file *file, void *priv,
				enum v4l2_buf_type buftype)
{
	struct vpif_fh *fh = priv;
	struct channel_obj *ch = fh->channel;
	struct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];

	if (buftype != V4L2_BUF_TYPE_VIDEO_OUTPUT) {
		vpif_err("buffer type not supported\n");
		return -EINVAL;
	}

	if (!fh->io_allowed[VPIF_VIDEO_INDEX]) {
		vpif_err("fh->io_allowed\n");
		return -EACCES;
	}

	if (!common->started) {
		vpif_err("channel->started\n");
		return -EINVAL;
	}

	if (mutex_lock_interruptible(&common->lock))
		return -ERESTARTSYS;

	if (buftype == V4L2_BUF_TYPE_VIDEO_OUTPUT) {
		/* disable channel */
		if (VPIF_CHANNEL2_VIDEO == ch->channel_id) {
			enable_channel2(0);
			channel2_intr_enable(0);
		}
		if ((VPIF_CHANNEL3_VIDEO == ch->channel_id) ||
					(2 == common->started)) {
			enable_channel3(0);
			channel3_intr_enable(0);
		}
	}

	common->started = 0;
	mutex_unlock(&common->lock);

	return videobuf_streamoff(&common->buffer_queue);
}