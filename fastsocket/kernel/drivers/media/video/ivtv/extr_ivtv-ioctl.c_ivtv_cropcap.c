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
struct yuv_playback_info {int osd_full_w; int osd_full_h; scalar_t__ track_osd; } ;
struct TYPE_4__ {int width; int height; scalar_t__ left; scalar_t__ top; } ;
struct TYPE_3__ {int numerator; int denominator; } ;
struct v4l2_cropcap {scalar_t__ type; TYPE_2__ bounds; TYPE_2__ defrect; TYPE_1__ pixelaspect; } ;
struct ivtv_open_id {int type; struct ivtv* itv; } ;
struct ivtv {scalar_t__ is_out_50hz; scalar_t__ is_50hz; struct yuv_playback_info yuv_info; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int IVTV_DEC_STREAM_TYPE_YUV ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 

__attribute__((used)) static int ivtv_cropcap(struct file *file, void *fh, struct v4l2_cropcap *cropcap)
{
	struct ivtv_open_id *id = fh;
	struct ivtv *itv = id->itv;
	struct yuv_playback_info *yi = &itv->yuv_info;
	int streamtype;

	streamtype = id->type;

	if (cropcap->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		return -EINVAL;
	cropcap->bounds.top = cropcap->bounds.left = 0;
	cropcap->bounds.width = 720;
	if (cropcap->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		cropcap->bounds.height = itv->is_50hz ? 576 : 480;
		cropcap->pixelaspect.numerator = itv->is_50hz ? 59 : 10;
		cropcap->pixelaspect.denominator = itv->is_50hz ? 54 : 11;
	} else if (streamtype == IVTV_DEC_STREAM_TYPE_YUV) {
		if (yi->track_osd) {
			cropcap->bounds.width = yi->osd_full_w;
			cropcap->bounds.height = yi->osd_full_h;
		} else {
			cropcap->bounds.width = 720;
			cropcap->bounds.height =
					itv->is_out_50hz ? 576 : 480;
		}
		cropcap->pixelaspect.numerator = itv->is_out_50hz ? 59 : 10;
		cropcap->pixelaspect.denominator = itv->is_out_50hz ? 54 : 11;
	} else {
		cropcap->bounds.height = itv->is_out_50hz ? 576 : 480;
		cropcap->pixelaspect.numerator = itv->is_out_50hz ? 59 : 10;
		cropcap->pixelaspect.denominator = itv->is_out_50hz ? 54 : 11;
	}
	cropcap->defrect = cropcap->bounds;
	return 0;
}