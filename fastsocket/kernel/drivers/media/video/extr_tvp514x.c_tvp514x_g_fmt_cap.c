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
struct v4l2_subdev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  bytesperline; } ;
struct TYPE_3__ {TYPE_2__ pix; } ;
struct v4l2_format {scalar_t__ type; TYPE_1__ fmt; } ;
struct tvp514x_decoder {TYPE_2__ pix; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  debug ; 
 struct tvp514x_decoder* to_decoder (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tvp514x_g_fmt_cap(struct v4l2_subdev *sd, struct v4l2_format *f)
{
	struct tvp514x_decoder *decoder = to_decoder(sd);

	if (f == NULL)
		return -EINVAL;

	if (f->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		/* only capture is supported */
		return -EINVAL;

	f->fmt.pix = decoder->pix;

	v4l2_dbg(1, debug, sd, "Current FMT: bytesperline - %d"
			"Width - %d, Height - %d",
			decoder->pix.bytesperline,
			decoder->pix.width, decoder->pix.height);
	return 0;
}