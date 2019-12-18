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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; int height; int width; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; } ;
struct cx18_av_state {int std; } ;
struct cx18 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_INFO_DEV (struct v4l2_subdev*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  CX18_ERR_DEV (struct v4l2_subdev*,char*,int,int) ; 
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_MBUS_FMT_FIXED ; 
 int V4L2_STD_525_60 ; 
 int cx18_av_read (struct cx18*,int) ; 
 int /*<<< orphan*/  cx18_av_write (struct cx18*,int,int) ; 
 struct cx18_av_state* to_cx18_av_state (struct v4l2_subdev*) ; 
 struct cx18* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int cx18_av_s_mbus_fmt(struct v4l2_subdev *sd, struct v4l2_mbus_framefmt *fmt)
{
	struct cx18_av_state *state = to_cx18_av_state(sd);
	struct cx18 *cx = v4l2_get_subdevdata(sd);
	int HSC, VSC, Vsrc, Hsrc, filter, Vlines;
	int is_50Hz = !(state->std & V4L2_STD_525_60);

	if (fmt->code != V4L2_MBUS_FMT_FIXED)
		return -EINVAL;

	fmt->field = V4L2_FIELD_INTERLACED;
	fmt->colorspace = V4L2_COLORSPACE_SMPTE170M;

	Vsrc = (cx18_av_read(cx, 0x476) & 0x3f) << 4;
	Vsrc |= (cx18_av_read(cx, 0x475) & 0xf0) >> 4;

	Hsrc = (cx18_av_read(cx, 0x472) & 0x3f) << 4;
	Hsrc |= (cx18_av_read(cx, 0x471) & 0xf0) >> 4;

	/*
	 * This adjustment reflects the excess of vactive, set in
	 * cx18_av_std_setup(), above standard values:
	 *
	 * 480 + 1 for 60 Hz systems
	 * 576 + 3 for 50 Hz systems
	 */
	Vlines = fmt->height + (is_50Hz ? 3 : 1);

	/*
	 * Invalid height and width scaling requests are:
	 * 1. width less than 1/16 of the source width
	 * 2. width greater than the source width
	 * 3. height less than 1/8 of the source height
	 * 4. height greater than the source height
	 */
	if ((fmt->width * 16 < Hsrc) || (Hsrc < fmt->width) ||
	    (Vlines * 8 < Vsrc) || (Vsrc < Vlines)) {
		CX18_ERR_DEV(sd, "%dx%d is not a valid size!\n",
			     fmt->width, fmt->height);
		return -ERANGE;
	}

	HSC = (Hsrc * (1 << 20)) / fmt->width - (1 << 20);
	VSC = (1 << 16) - (Vsrc * (1 << 9) / Vlines - (1 << 9));
	VSC &= 0x1fff;

	if (fmt->width >= 385)
		filter = 0;
	else if (fmt->width > 192)
		filter = 1;
	else if (fmt->width > 96)
		filter = 2;
	else
		filter = 3;

	CX18_DEBUG_INFO_DEV(sd,
			    "decoder set size %dx%d -> scale  %ux%u\n",
			    fmt->width, fmt->height, HSC, VSC);

	/* HSCALE=HSC */
	cx18_av_write(cx, 0x418, HSC & 0xff);
	cx18_av_write(cx, 0x419, (HSC >> 8) & 0xff);
	cx18_av_write(cx, 0x41a, HSC >> 16);
	/* VSCALE=VSC */
	cx18_av_write(cx, 0x41c, VSC & 0xff);
	cx18_av_write(cx, 0x41d, VSC >> 8);
	/* VS_INTRLACE=1 VFILT=filter */
	cx18_av_write(cx, 0x41e, 0x8 | filter);
	return 0;
}