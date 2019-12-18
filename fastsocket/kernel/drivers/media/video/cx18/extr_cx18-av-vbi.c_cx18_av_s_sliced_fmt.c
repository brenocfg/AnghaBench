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
struct cx18_av_state {int std; int slicer_line_delay; } ;
struct cx18 {struct cx18_av_state av_state; } ;

/* Variables and functions */
#define  V4L2_SLICED_CAPTION_525 131 
#define  V4L2_SLICED_TELETEXT_B 130 
#define  V4L2_SLICED_VPS 129 
#define  V4L2_SLICED_WSS_625 128 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  cx18_av_std_setup (struct cx18*) ; 
 int /*<<< orphan*/  cx18_av_write (struct cx18*,int,int) ; 
 struct cx18* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

int cx18_av_s_sliced_fmt(struct v4l2_subdev *sd, struct v4l2_sliced_vbi_format *svbi)
{
	struct cx18 *cx = v4l2_get_subdevdata(sd);
	struct cx18_av_state *state = &cx->av_state;
	int is_pal = !(state->std & V4L2_STD_525_60);
	int i, x;
	u8 lcr[24];

	for (x = 0; x <= 23; x++)
		lcr[x] = 0x00;

	/* Setup standard */
	cx18_av_std_setup(cx);

	/* Sliced VBI */
	cx18_av_write(cx, 0x404, 0x32);	/* Ancillary data */
	cx18_av_write(cx, 0x406, 0x13);
	cx18_av_write(cx, 0x47f, state->slicer_line_delay);

	/* Force impossible lines to 0 */
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

	/* Build register values for requested service lines */
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
			cx18_av_write(cx, i, lcr[6 + x]);
	} else {
		for (x = 1, i = 0x424; i <= 0x430; i++, x++)
			cx18_av_write(cx, i, lcr[9 + x]);
		for (i = 0x431; i <= 0x434; i++)
			cx18_av_write(cx, i, 0);
	}

	cx18_av_write(cx, 0x43c, 0x16);
	/* Should match vblank set in cx18_av_std_setup() */
	cx18_av_write(cx, 0x474, is_pal ? 38 : 26);
	return 0;
}