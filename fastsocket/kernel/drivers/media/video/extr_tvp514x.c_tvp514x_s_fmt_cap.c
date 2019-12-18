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
struct v4l2_subdev {int dummy; } ;
struct v4l2_pix_format {int dummy; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {scalar_t__ type; TYPE_1__ fmt; } ;
struct tvp514x_decoder {struct v4l2_pix_format pix; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 struct tvp514x_decoder* to_decoder (struct v4l2_subdev*) ; 
 int tvp514x_try_fmt_cap (struct v4l2_subdev*,struct v4l2_format*) ; 

__attribute__((used)) static int
tvp514x_s_fmt_cap(struct v4l2_subdev *sd, struct v4l2_format *f)
{
	struct tvp514x_decoder *decoder = to_decoder(sd);
	struct v4l2_pix_format *pix;
	int rval;

	if (f == NULL)
		return -EINVAL;

	if (f->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		/* only capture is supported */
		return -EINVAL;

	pix = &f->fmt.pix;
	rval = tvp514x_try_fmt_cap(sd, f);
	if (rval)
		return rval;

		decoder->pix = *pix;

	return rval;
}