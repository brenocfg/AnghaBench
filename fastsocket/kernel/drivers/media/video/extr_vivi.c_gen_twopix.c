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
struct vivi_fh {unsigned char** bars; TYPE_1__* fmt; } ;
struct TYPE_2__ {int fourcc; } ;

/* Variables and functions */
#define  V4L2_PIX_FMT_RGB555 133 
#define  V4L2_PIX_FMT_RGB555X 132 
#define  V4L2_PIX_FMT_RGB565 131 
#define  V4L2_PIX_FMT_RGB565X 130 
#define  V4L2_PIX_FMT_UYVY 129 
#define  V4L2_PIX_FMT_YUYV 128 

__attribute__((used)) static void gen_twopix(struct vivi_fh *fh, unsigned char *buf, int colorpos)
{
	unsigned char r_y, g_u, b_v;
	unsigned char *p;
	int color;

	r_y = fh->bars[colorpos][0]; /* R or precalculated Y */
	g_u = fh->bars[colorpos][1]; /* G or precalculated U */
	b_v = fh->bars[colorpos][2]; /* B or precalculated V */

	for (color = 0; color < 4; color++) {
		p = buf + color;

		switch (fh->fmt->fourcc) {
		case V4L2_PIX_FMT_YUYV:
			switch (color) {
			case 0:
			case 2:
				*p = r_y;
				break;
			case 1:
				*p = g_u;
				break;
			case 3:
				*p = b_v;
				break;
			}
			break;
		case V4L2_PIX_FMT_UYVY:
			switch (color) {
			case 1:
			case 3:
				*p = r_y;
				break;
			case 0:
				*p = g_u;
				break;
			case 2:
				*p = b_v;
				break;
			}
			break;
		case V4L2_PIX_FMT_RGB565:
			switch (color) {
			case 0:
			case 2:
				*p = (g_u << 5) | b_v;
				break;
			case 1:
			case 3:
				*p = (r_y << 3) | (g_u >> 3);
				break;
			}
			break;
		case V4L2_PIX_FMT_RGB565X:
			switch (color) {
			case 0:
			case 2:
				*p = (r_y << 3) | (g_u >> 3);
				break;
			case 1:
			case 3:
				*p = (g_u << 5) | b_v;
				break;
			}
			break;
		case V4L2_PIX_FMT_RGB555:
			switch (color) {
			case 0:
			case 2:
				*p = (g_u << 5) | b_v;
				break;
			case 1:
			case 3:
				*p = (r_y << 2) | (g_u >> 3);
				break;
			}
			break;
		case V4L2_PIX_FMT_RGB555X:
			switch (color) {
			case 0:
			case 2:
				*p = (r_y << 2) | (g_u >> 3);
				break;
			case 1:
			case 3:
				*p = (g_u << 5) | b_v;
				break;
			}
			break;
		}
	}
}