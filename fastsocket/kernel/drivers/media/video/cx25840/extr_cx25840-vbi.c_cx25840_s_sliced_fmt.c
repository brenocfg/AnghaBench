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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_sliced_vbi_format {int** service_lines; } ;
struct i2c_client {int dummy; } ;
struct cx25840_state {int std; } ;

/* Variables and functions */
#define  V4L2_SLICED_CAPTION_525 131 
#define  V4L2_SLICED_TELETEXT_B 130 
#define  V4L2_SLICED_VPS 129 
#define  V4L2_SLICED_WSS_625 128 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  cx25840_std_setup (struct i2c_client*) ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 struct cx25840_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

int cx25840_s_sliced_fmt(struct v4l2_subdev *sd, struct v4l2_sliced_vbi_format *svbi)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct cx25840_state *state = to_state(sd);
	int is_pal = !(state->std & V4L2_STD_525_60);
	int vbi_offset = is_pal ? 1 : 0;
	int i, x;
	u8 lcr[24];

	for (x = 0; x <= 23; x++)
		lcr[x] = 0x00;

	/* Setup standard */
	cx25840_std_setup(client);

	/* Sliced VBI */
	cx25840_write(client, 0x404, 0x32);	/* Ancillary data */
	cx25840_write(client, 0x406, 0x13);
	cx25840_write(client, 0x47f, vbi_offset);

	if (is_pal) {
		for (i = 0; i <= 6; i++)
			svbi->service_lines[0][i] =
				svbi->service_lines[1][i] = 0;
	} else {
		for (i = 0; i <= 9; i++)
			svbi->service_lines[0][i] =
				svbi->service_lines[1][i] = 0;

		for (i = 22; i <= 23; i++)
			svbi->service_lines[0][i] =
				svbi->service_lines[1][i] = 0;
	}

	for (i = 7; i <= 23; i++) {
		for (x = 0; x <= 1; x++) {
			switch (svbi->service_lines[1-x][i]) {
			case V4L2_SLICED_TELETEXT_B:
				lcr[i] |= 1 << (4 * x);
				break;
			case V4L2_SLICED_WSS_625:
				lcr[i] |= 4 << (4 * x);
				break;
			case V4L2_SLICED_CAPTION_525:
				lcr[i] |= 6 << (4 * x);
				break;
			case V4L2_SLICED_VPS:
				lcr[i] |= 9 << (4 * x);
				break;
			}
		}
	}

	if (is_pal) {
		for (x = 1, i = 0x424; i <= 0x434; i++, x++)
			cx25840_write(client, i, lcr[6 + x]);
	} else {
		for (x = 1, i = 0x424; i <= 0x430; i++, x++)
			cx25840_write(client, i, lcr[9 + x]);
		for (i = 0x431; i <= 0x434; i++)
			cx25840_write(client, i, 0);
	}

	cx25840_write(client, 0x43c, 0x16);
	cx25840_write(client, 0x474, is_pal ? 0x2a : 0x22);
	return 0;
}