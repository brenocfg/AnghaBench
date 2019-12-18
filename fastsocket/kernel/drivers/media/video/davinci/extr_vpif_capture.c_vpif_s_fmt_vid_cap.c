#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vpif_fh {int initialized; int /*<<< orphan*/  prio; struct channel_obj* channel; } ;
struct v4l2_pix_format {int dummy; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct common_obj {int /*<<< orphan*/  lock; struct v4l2_format fmt; scalar_t__ started; } ;
struct channel_obj {scalar_t__ channel_id; int /*<<< orphan*/  prio; struct common_obj* common; } ;

/* Variables and functions */
 int EBUSY ; 
 int ERESTARTSYS ; 
 scalar_t__ VPIF_CHANNEL0_VIDEO ; 
 scalar_t__ VPIF_CHANNEL1_VIDEO ; 
 size_t VPIF_VIDEO_INDEX ; 
 int /*<<< orphan*/  debug ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int v4l2_prio_check (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vpif_check_format (struct channel_obj*,struct v4l2_pix_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vpif_s_fmt_vid_cap(struct file *file, void *priv,
				struct v4l2_format *fmt)
{
	struct vpif_fh *fh = priv;
	struct channel_obj *ch = fh->channel;
	struct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	struct v4l2_pix_format *pixfmt;
	int ret = 0;

	vpif_dbg(2, debug, "VIDIOC_S_FMT\n");

	/* If streaming is started, return error */
	if (common->started) {
		vpif_dbg(1, debug, "Streaming is started\n");
		return -EBUSY;
	}

	if ((VPIF_CHANNEL0_VIDEO == ch->channel_id) ||
	    (VPIF_CHANNEL1_VIDEO == ch->channel_id)) {
		if (!fh->initialized) {
			vpif_dbg(1, debug, "Channel Busy\n");
			return -EBUSY;
		}
	}

	ret = v4l2_prio_check(&ch->prio, &fh->prio);
	if (0 != ret)
		return ret;

	fh->initialized = 1;

	pixfmt = &fmt->fmt.pix;
	/* Check for valid field format */
	ret = vpif_check_format(ch, pixfmt, 0);

	if (ret)
		return ret;
	/* store the format in the channel object */
	if (mutex_lock_interruptible(&common->lock))
		return -ERESTARTSYS;

	common->fmt = *fmt;
	mutex_unlock(&common->lock);

	return 0;
}