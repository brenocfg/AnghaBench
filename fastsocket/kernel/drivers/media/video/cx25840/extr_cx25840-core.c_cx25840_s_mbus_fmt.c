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
struct i2c_client {int dummy; } ;
struct cx25840_state {int std; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_MBUS_FMT_FIXED ; 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  cx25840_debug ; 
 int cx25840_read (struct i2c_client*,int) ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 struct cx25840_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  v4l_err (struct i2c_client*,char*,int,int) ; 

__attribute__((used)) static int cx25840_s_mbus_fmt(struct v4l2_subdev *sd, struct v4l2_mbus_framefmt *fmt)
{
	struct cx25840_state *state = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int HSC, VSC, Vsrc, Hsrc, filter, Vlines;
	int is_50Hz = !(state->std & V4L2_STD_525_60);

	if (fmt->code != V4L2_MBUS_FMT_FIXED)
		return -EINVAL;

	fmt->field = V4L2_FIELD_INTERLACED;
	fmt->colorspace = V4L2_COLORSPACE_SMPTE170M;

	Vsrc = (cx25840_read(client, 0x476) & 0x3f) << 4;
	Vsrc |= (cx25840_read(client, 0x475) & 0xf0) >> 4;

	Hsrc = (cx25840_read(client, 0x472) & 0x3f) << 4;
	Hsrc |= (cx25840_read(client, 0x471) & 0xf0) >> 4;

	Vlines = fmt->height + (is_50Hz ? 4 : 7);

	if ((fmt->width * 16 < Hsrc) || (Hsrc < fmt->width) ||
			(Vlines * 8 < Vsrc) || (Vsrc < Vlines)) {
		v4l_err(client, "%dx%d is not a valid size!\n",
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

	v4l_dbg(1, cx25840_debug, client, "decoder set size %dx%d -> scale  %ux%u\n",
			fmt->width, fmt->height, HSC, VSC);

	/* HSCALE=HSC */
	cx25840_write(client, 0x418, HSC & 0xff);
	cx25840_write(client, 0x419, (HSC >> 8) & 0xff);
	cx25840_write(client, 0x41a, HSC >> 16);
	/* VSCALE=VSC */
	cx25840_write(client, 0x41c, VSC & 0xff);
	cx25840_write(client, 0x41d, VSC >> 8);
	/* VS_INTRLACE=1 VFILT=filter */
	cx25840_write(client, 0x41e, 0x8 | filter);
	return 0;
}