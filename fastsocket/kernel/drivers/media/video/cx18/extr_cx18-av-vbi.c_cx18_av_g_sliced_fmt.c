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
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_sliced_vbi_format {int** service_lines; int service_set; } ;
struct cx18_av_state {int std; } ;
struct cx18 {struct cx18_av_state av_state; } ;

/* Variables and functions */
#define  V4L2_SLICED_CAPTION_525 131 
#define  V4L2_SLICED_TELETEXT_B 130 
#define  V4L2_SLICED_VPS 129 
#define  V4L2_SLICED_WSS_625 128 
 int V4L2_STD_525_60 ; 
 int cx18_av_read (struct cx18*,int) ; 
 int /*<<< orphan*/  memset (struct v4l2_sliced_vbi_format*,int /*<<< orphan*/ ,int) ; 
 struct cx18* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

int cx18_av_g_sliced_fmt(struct v4l2_subdev *sd, struct v4l2_sliced_vbi_format *svbi)
{
	struct cx18 *cx = v4l2_get_subdevdata(sd);
	struct cx18_av_state *state = &cx->av_state;
	static const u16 lcr2vbi[] = {
		0, V4L2_SLICED_TELETEXT_B, 0,	/* 1 */
		0, V4L2_SLICED_WSS_625, 0,	/* 4 */
		V4L2_SLICED_CAPTION_525,	/* 6 */
		0, 0, V4L2_SLICED_VPS, 0, 0,	/* 9 */
		0, 0, 0, 0
	};
	int is_pal = !(state->std & V4L2_STD_525_60);
	int i;

	memset(svbi, 0, sizeof(*svbi));
	/* we're done if raw VBI is active */
	if ((cx18_av_read(cx, 0x404) & 0x10) == 0)
		return 0;

	if (is_pal) {
		for (i = 7; i <= 23; i++) {
			u8 v = cx18_av_read(cx, 0x424 + i - 7);

			svbi->service_lines[0][i] = lcr2vbi[v >> 4];
			svbi->service_lines[1][i] = lcr2vbi[v & 0xf];
			svbi->service_set |= svbi->service_lines[0][i] |
				svbi->service_lines[1][i];
		}
	} else {
		for (i = 10; i <= 21; i++) {
			u8 v = cx18_av_read(cx, 0x424 + i - 10);

			svbi->service_lines[0][i] = lcr2vbi[v >> 4];
			svbi->service_lines[1][i] = lcr2vbi[v & 0xf];
			svbi->service_set |= svbi->service_lines[0][i] |
				svbi->service_lines[1][i];
		}
	}
	return 0;
}