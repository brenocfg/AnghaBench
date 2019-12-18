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
struct vivi_fh {size_t input; unsigned char** bars; TYPE_1__* fmt; struct vivi_dev* dev; } ;
struct vivi_dev {size_t input; } ;
struct TYPE_4__ {unsigned char** bar; } ;
struct TYPE_3__ {int fourcc; } ;

/* Variables and functions */
 unsigned char TO_U (unsigned char,unsigned char,unsigned char) ; 
 unsigned char TO_V (unsigned char,unsigned char,unsigned char) ; 
 unsigned char TO_Y (unsigned char,unsigned char,unsigned char) ; 
#define  V4L2_PIX_FMT_RGB555 133 
#define  V4L2_PIX_FMT_RGB555X 132 
#define  V4L2_PIX_FMT_RGB565 131 
#define  V4L2_PIX_FMT_RGB565X 130 
#define  V4L2_PIX_FMT_UYVY 129 
#define  V4L2_PIX_FMT_YUYV 128 
 TYPE_2__* bars ; 

__attribute__((used)) static void precalculate_bars(struct vivi_fh *fh)
{
	struct vivi_dev *dev = fh->dev;
	unsigned char r, g, b;
	int k, is_yuv;

	fh->input = dev->input;

	for (k = 0; k < 8; k++) {
		r = bars[fh->input].bar[k][0];
		g = bars[fh->input].bar[k][1];
		b = bars[fh->input].bar[k][2];
		is_yuv = 0;

		switch (fh->fmt->fourcc) {
		case V4L2_PIX_FMT_YUYV:
		case V4L2_PIX_FMT_UYVY:
			is_yuv = 1;
			break;
		case V4L2_PIX_FMT_RGB565:
		case V4L2_PIX_FMT_RGB565X:
			r >>= 3;
			g >>= 2;
			b >>= 3;
			break;
		case V4L2_PIX_FMT_RGB555:
		case V4L2_PIX_FMT_RGB555X:
			r >>= 3;
			g >>= 3;
			b >>= 3;
			break;
		}

		if (is_yuv) {
			fh->bars[k][0] = TO_Y(r, g, b);	/* Luma */
			fh->bars[k][1] = TO_U(r, g, b);	/* Cb */
			fh->bars[k][2] = TO_V(r, g, b);	/* Cr */
		} else {
			fh->bars[k][0] = r;
			fh->bars[k][1] = g;
			fh->bars[k][2] = b;
		}
	}

}