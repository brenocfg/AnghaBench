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
typedef  int u32 ;
struct TYPE_4__ {int width; int height; } ;
struct zoran_fh {int* overlay_mask; TYPE_2__ overlay_settings; struct zoran* zr; } ;
struct zoran {int dummy; } ;
struct TYPE_3__ {int left; int top; int width; int height; } ;
struct v4l2_clip {TYPE_1__ c; } ;

/* Variables and functions */
 unsigned int BUZ_MAX_HEIGHT ; 
 int BUZ_MAX_WIDTH ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,unsigned int) ; 

void write_overlay_mask(struct zoran_fh *fh, struct v4l2_clip *vp, int count)
{
	struct zoran *zr = fh->zr;
	unsigned mask_line_size = (BUZ_MAX_WIDTH + 31) / 32;
	u32 *mask;
	int x, y, width, height;
	unsigned i, j, k;
	u32 reg;

	/* fill mask with one bits */
	memset(fh->overlay_mask, ~0, mask_line_size * 4 * BUZ_MAX_HEIGHT);
	reg = 0;

	for (i = 0; i < count; ++i) {
		/* pick up local copy of clip */
		x = vp[i].c.left;
		y = vp[i].c.top;
		width = vp[i].c.width;
		height = vp[i].c.height;

		/* trim clips that extend beyond the window */
		if (x < 0) {
			width += x;
			x = 0;
		}
		if (y < 0) {
			height += y;
			y = 0;
		}
		if (x + width > fh->overlay_settings.width) {
			width = fh->overlay_settings.width - x;
		}
		if (y + height > fh->overlay_settings.height) {
			height = fh->overlay_settings.height - y;
		}

		/* ignore degenerate clips */
		if (height <= 0) {
			continue;
		}
		if (width <= 0) {
			continue;
		}

		/* apply clip for each scan line */
		for (j = 0; j < height; ++j) {
			/* reset bit for each pixel */
			/* this can be optimized later if need be */
			mask = fh->overlay_mask + (y + j) * mask_line_size;
			for (k = 0; k < width; ++k) {
				mask[(x + k) / 32] &=
				    ~((u32) 1 << (x + k) % 32);
			}
		}
	}
}