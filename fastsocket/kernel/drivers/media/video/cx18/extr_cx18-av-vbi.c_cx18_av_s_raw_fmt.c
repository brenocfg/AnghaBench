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
struct v4l2_vbi_format {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct cx18_av_state {int slicer_line_delay; } ;
struct cx18 {struct cx18_av_state av_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx18_av_std_setup (struct cx18*) ; 
 int /*<<< orphan*/  cx18_av_write (struct cx18*,int,int) ; 
 struct cx18* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

int cx18_av_s_raw_fmt(struct v4l2_subdev *sd, struct v4l2_vbi_format *fmt)
{
	struct cx18 *cx = v4l2_get_subdevdata(sd);
	struct cx18_av_state *state = &cx->av_state;

	/* Setup standard */
	cx18_av_std_setup(cx);

	/* VBI Offset */
	cx18_av_write(cx, 0x47f, state->slicer_line_delay);
	cx18_av_write(cx, 0x404, 0x2e);
	return 0;
}