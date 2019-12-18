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
struct v4l2_fmtdesc {int index; scalar_t__ type; } ;
struct tvp514x_decoder {int num_fmts; TYPE_1__* fmt_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  description; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  memcpy (struct v4l2_fmtdesc*,TYPE_1__*,int) ; 
 struct tvp514x_decoder* to_decoder (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tvp514x_enum_fmt_cap(struct v4l2_subdev *sd, struct v4l2_fmtdesc *fmt)
{
	struct tvp514x_decoder *decoder = to_decoder(sd);
	int index;

	if (fmt == NULL)
		return -EINVAL;

	index = fmt->index;
	if ((index >= decoder->num_fmts) || (index < 0))
		/* Index out of bound */
		return -EINVAL;

	if (fmt->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		/* only capture is supported */
		return -EINVAL;

	memcpy(fmt, &decoder->fmt_list[index],
		sizeof(struct v4l2_fmtdesc));

	v4l2_dbg(1, debug, sd, "Current FMT: index - %d (%s)",
			decoder->fmt_list[index].index,
			decoder->fmt_list[index].description);
	return 0;
}