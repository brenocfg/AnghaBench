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
struct v4l2_vbi_format {scalar_t__ sample_format; int* count; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TVP5150_LUMA_PROC_CTL_1 ; 
 int /*<<< orphan*/  TVP5150_VERT_BLANKING_START ; 
 int /*<<< orphan*/  TVP5150_VERT_BLANKING_STOP ; 
 scalar_t__ V4L2_PIX_FMT_GREY ; 
 int /*<<< orphan*/  tvp5150_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tvp5150_s_raw_fmt(struct v4l2_subdev *sd, struct v4l2_vbi_format *fmt)
{
	/* this is for capturing 36 raw vbi lines
	   if there's a way to cut off the beginning 2 vbi lines
	   with the tvp5150 then the vbi line count could be lowered
	   to 17 lines/field again, although I couldn't find a register
	   which could do that cropping */
	if (fmt->sample_format == V4L2_PIX_FMT_GREY)
		tvp5150_write(sd, TVP5150_LUMA_PROC_CTL_1, 0x70);
	if (fmt->count[0] == 18 && fmt->count[1] == 18) {
		tvp5150_write(sd, TVP5150_VERT_BLANKING_START, 0x00);
		tvp5150_write(sd, TVP5150_VERT_BLANKING_STOP, 0x01);
	}
	return 0;
}