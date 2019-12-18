#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_9__ {size_t field; TYPE_2__ w; } ;
struct TYPE_6__ {TYPE_4__ win; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct saa7146_vv {struct saa7146_fh* video_fh; int /*<<< orphan*/  video_status; TYPE_3__* ov_fmt; TYPE_5__* ov_data; } ;
struct TYPE_10__ {TYPE_4__ win; int /*<<< orphan*/ * fh; } ;
struct saa7146_fh {TYPE_5__ ov; struct saa7146_dev* dev; } ;
struct saa7146_dev {struct saa7146_vv* vv_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_D (char*) ; 
 int /*<<< orphan*/  DEB_EE (char*) ; 
 int EAGAIN ; 
 int EBUSY ; 
 scalar_t__ IS_CAPTURE_ACTIVE (struct saa7146_fh*) ; 
 scalar_t__ IS_OVERLAY_ACTIVE (struct saa7146_fh*) ; 
 int RESOURCE_DMA1_HPS ; 
 int RESOURCE_DMA2_CLP ; 
 int /*<<< orphan*/  STATUS_OVERLAY ; 
 int saa7146_enable_overlay (struct saa7146_fh*) ; 
 int /*<<< orphan*/  saa7146_res_free (struct saa7146_fh*,int) ; 
 scalar_t__ saa7146_res_get (struct saa7146_fh*,int) ; 
 int /*<<< orphan*/ * v4l2_field_names ; 
 int vidioc_try_fmt_vid_overlay (int /*<<< orphan*/ *,struct saa7146_fh*,struct v4l2_format*) ; 

int saa7146_start_preview(struct saa7146_fh *fh)
{
	struct saa7146_dev *dev = fh->dev;
	struct saa7146_vv *vv = dev->vv_data;
	struct v4l2_format fmt;
	int ret = 0, err = 0;

	DEB_EE(("dev:%p, fh:%p\n",dev,fh));

	/* check if we have overlay informations */
	if( NULL == fh->ov.fh ) {
		DEB_D(("no overlay data available. try S_FMT first.\n"));
		return -EAGAIN;
	}

	/* check if streaming capture is running */
	if (IS_CAPTURE_ACTIVE(fh) != 0) {
		DEB_D(("streaming capture is active.\n"));
		return -EBUSY;
	}

	/* check if overlay is running */
	if (IS_OVERLAY_ACTIVE(fh) != 0) {
		if (vv->video_fh == fh) {
			DEB_D(("overlay is already active.\n"));
			return 0;
		}
		DEB_D(("overlay is already active in another open.\n"));
		return -EBUSY;
	}

	if (0 == saa7146_res_get(fh, RESOURCE_DMA1_HPS|RESOURCE_DMA2_CLP)) {
		DEB_D(("cannot get necessary overlay resources\n"));
		return -EBUSY;
	}

	fmt.fmt.win = fh->ov.win;
	err = vidioc_try_fmt_vid_overlay(NULL, fh, &fmt);
	if (0 != err) {
		saa7146_res_free(vv->video_fh, RESOURCE_DMA1_HPS|RESOURCE_DMA2_CLP);
		return -EBUSY;
	}
	fh->ov.win = fmt.fmt.win;
	vv->ov_data = &fh->ov;

	DEB_D(("%dx%d+%d+%d %s field=%s\n",
		fh->ov.win.w.width,fh->ov.win.w.height,
		fh->ov.win.w.left,fh->ov.win.w.top,
		vv->ov_fmt->name,v4l2_field_names[fh->ov.win.field]));

	if (0 != (ret = saa7146_enable_overlay(fh))) {
		DEB_D(("enabling overlay failed: %d\n",ret));
		saa7146_res_free(vv->video_fh, RESOURCE_DMA1_HPS|RESOURCE_DMA2_CLP);
		return ret;
	}

	vv->video_status = STATUS_OVERLAY;
	vv->video_fh = fh;

	return 0;
}