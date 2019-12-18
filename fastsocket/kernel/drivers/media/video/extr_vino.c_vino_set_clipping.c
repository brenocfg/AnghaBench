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
struct TYPE_3__ {unsigned int left; unsigned int top; unsigned int right; unsigned int bottom; } ;
struct vino_channel_settings {size_t data_norm; unsigned int decimation; int /*<<< orphan*/  line_size; TYPE_1__ clipping; } ;
struct TYPE_4__ {unsigned int width; unsigned int height; } ;

/* Variables and functions */
 unsigned int VINO_MIN_HEIGHT ; 
 unsigned int VINO_MIN_WIDTH ; 
 int /*<<< orphan*/  dprintk (char*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_2__* vino_data_norms ; 
 int /*<<< orphan*/  vino_update_line_size (struct vino_channel_settings*) ; 

__attribute__((used)) static void vino_set_clipping(struct vino_channel_settings *vcs,
			      unsigned int x, unsigned int y,
			      unsigned int w, unsigned int h)
{
	unsigned int maxwidth, maxheight;
	unsigned int d;

	maxwidth = vino_data_norms[vcs->data_norm].width;
	maxheight = vino_data_norms[vcs->data_norm].height;
	d = vcs->decimation;

	y &= ~1;	/* odd/even fields */

	if (x > maxwidth) {
		x = 0;
	}
	if (y > maxheight) {
		y = 0;
	}

	if (((w / d) < VINO_MIN_WIDTH)
	    || ((h / d) < VINO_MIN_HEIGHT)) {
		w = VINO_MIN_WIDTH * d;
		h = VINO_MIN_HEIGHT * d;
	}

	if ((x + w) > maxwidth) {
		w = maxwidth - x;
		if ((w / d) < VINO_MIN_WIDTH)
			x = maxwidth - VINO_MIN_WIDTH * d;
	}
	if ((y + h) > maxheight) {
		h = maxheight - y;
		if ((h / d) < VINO_MIN_HEIGHT)
			y = maxheight - VINO_MIN_HEIGHT * d;
	}

	vcs->clipping.left = x;
	vcs->clipping.top = y;
	vcs->clipping.right = x + w;
	vcs->clipping.bottom = y + h;

	vino_update_line_size(vcs);

	dprintk("clipping %d, %d, %d, %d / %d - %d\n",
		vcs->clipping.left, vcs->clipping.top, vcs->clipping.right,
		vcs->clipping.bottom, vcs->decimation, vcs->line_size);
}