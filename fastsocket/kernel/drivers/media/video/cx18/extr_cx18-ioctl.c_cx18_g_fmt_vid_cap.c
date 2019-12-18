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
struct v4l2_pix_format {int height; int sizeimage; int bytesperline; int /*<<< orphan*/  pixelformat; scalar_t__ priv; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  width; } ;
struct TYPE_3__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct cx18_open_id {scalar_t__ type; struct cx18* cx; } ;
struct TYPE_4__ {int height; int /*<<< orphan*/  width; } ;
struct cx18 {TYPE_2__ params; } ;

/* Variables and functions */
 scalar_t__ CX18_ENC_STREAM_TYPE_YUV ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_HM12 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_MPEG ; 

__attribute__((used)) static int cx18_g_fmt_vid_cap(struct file *file, void *fh,
				struct v4l2_format *fmt)
{
	struct cx18_open_id *id = fh;
	struct cx18 *cx = id->cx;
	struct v4l2_pix_format *pixfmt = &fmt->fmt.pix;

	pixfmt->width = cx->params.width;
	pixfmt->height = cx->params.height;
	pixfmt->colorspace = V4L2_COLORSPACE_SMPTE170M;
	pixfmt->field = V4L2_FIELD_INTERLACED;
	pixfmt->priv = 0;
	if (id->type == CX18_ENC_STREAM_TYPE_YUV) {
		pixfmt->pixelformat = V4L2_PIX_FMT_HM12;
		/* YUV size is (Y=(h*720) + UV=(h*(720/2))) */
		pixfmt->sizeimage = pixfmt->height * 720 * 3 / 2;
		pixfmt->bytesperline = 720;
	} else {
		pixfmt->pixelformat = V4L2_PIX_FMT_MPEG;
		pixfmt->sizeimage = 128 * 1024;
		pixfmt->bytesperline = 0;
	}
	return 0;
}