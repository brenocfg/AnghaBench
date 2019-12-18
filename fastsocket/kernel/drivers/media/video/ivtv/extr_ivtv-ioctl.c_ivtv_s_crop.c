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
struct TYPE_2__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct yuv_playback_info {TYPE_1__ main_rect; } ;
struct v4l2_crop {scalar_t__ type; TYPE_1__ c; } ;
struct ivtv_open_id {int type; struct ivtv* itv; } ;
struct ivtv {int v4l2_cap; TYPE_1__ main_rect; struct yuv_playback_info yuv_info; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_OSD_SET_FRAMEBUFFER_WINDOW ; 
 int EINVAL ; 
 int IVTV_DEC_STREAM_TYPE_YUV ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ivtv_s_crop(struct file *file, void *fh, struct v4l2_crop *crop)
{
	struct ivtv_open_id *id = fh;
	struct ivtv *itv = id->itv;
	struct yuv_playback_info *yi = &itv->yuv_info;
	int streamtype;

	streamtype = id->type;

	if (crop->type == V4L2_BUF_TYPE_VIDEO_OUTPUT &&
	    (itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT)) {
		if (streamtype == IVTV_DEC_STREAM_TYPE_YUV) {
			yi->main_rect = crop->c;
			return 0;
		} else {
			if (!ivtv_vapi(itv, CX2341X_OSD_SET_FRAMEBUFFER_WINDOW, 4,
				crop->c.width, crop->c.height, crop->c.left, crop->c.top)) {
				itv->main_rect = crop->c;
				return 0;
			}
		}
		return -EINVAL;
	}
	return -EINVAL;
}