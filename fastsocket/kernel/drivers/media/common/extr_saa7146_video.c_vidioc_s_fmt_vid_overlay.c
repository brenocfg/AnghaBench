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
struct TYPE_4__ {int clipcount; int /*<<< orphan*/  clips; } ;
struct TYPE_5__ {TYPE_1__ win; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct v4l2_clip {int dummy; } ;
struct saa7146_vv {int dummy; } ;
struct TYPE_6__ {int nclips; struct saa7146_fh* fh; int /*<<< orphan*/  clips; TYPE_1__ win; } ;
struct saa7146_fh {TYPE_3__ ov; struct saa7146_dev* dev; } ;
struct saa7146_dev {struct saa7146_vv* vv_data; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_EE (char*) ; 
 int EFAULT ; 
 scalar_t__ IS_OVERLAY_ACTIVE (struct saa7146_fh*) ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saa7146_start_preview (struct saa7146_fh*) ; 
 int /*<<< orphan*/  saa7146_stop_preview (struct saa7146_fh*) ; 
 int vidioc_try_fmt_vid_overlay (struct file*,struct saa7146_fh*,struct v4l2_format*) ; 

__attribute__((used)) static int vidioc_s_fmt_vid_overlay(struct file *file, void *__fh, struct v4l2_format *f)
{
	struct saa7146_fh *fh = __fh;
	struct saa7146_dev *dev = fh->dev;
	struct saa7146_vv *vv = dev->vv_data;
	int err;

	DEB_EE(("V4L2_BUF_TYPE_VIDEO_OVERLAY: dev:%p, fh:%p\n", dev, fh));
	err = vidioc_try_fmt_vid_overlay(file, fh, f);
	if (0 != err)
		return err;
	fh->ov.win    = f->fmt.win;
	fh->ov.nclips = f->fmt.win.clipcount;
	if (fh->ov.nclips > 16)
		fh->ov.nclips = 16;
	if (copy_from_user(fh->ov.clips, f->fmt.win.clips,
				sizeof(struct v4l2_clip) * fh->ov.nclips)) {
		return -EFAULT;
	}

	/* fh->ov.fh is used to indicate that we have valid overlay informations, too */
	fh->ov.fh = fh;

	/* check if our current overlay is active */
	if (IS_OVERLAY_ACTIVE(fh) != 0) {
		saa7146_stop_preview(fh);
		saa7146_start_preview(fh);
	}
	return 0;
}