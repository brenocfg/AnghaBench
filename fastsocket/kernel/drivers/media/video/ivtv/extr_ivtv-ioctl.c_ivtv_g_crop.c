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
struct yuv_playback_info {int /*<<< orphan*/  main_rect; } ;
struct v4l2_crop {scalar_t__ type; int /*<<< orphan*/  c; } ;
struct ivtv_open_id {int type; struct ivtv* itv; } ;
struct ivtv {int v4l2_cap; int /*<<< orphan*/  main_rect; struct yuv_playback_info yuv_info; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int IVTV_DEC_STREAM_TYPE_YUV ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 

__attribute__((used)) static int ivtv_g_crop(struct file *file, void *fh, struct v4l2_crop *crop)
{
	struct ivtv_open_id *id = fh;
	struct ivtv *itv = id->itv;
	struct yuv_playback_info *yi = &itv->yuv_info;
	int streamtype;

	streamtype = id->type;

	if (crop->type == V4L2_BUF_TYPE_VIDEO_OUTPUT &&
	    (itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT)) {
		if (streamtype == IVTV_DEC_STREAM_TYPE_YUV)
			crop->c = yi->main_rect;
		else
			crop->c = itv->main_rect;
		return 0;
	}
	return -EINVAL;
}