#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct plane_info {int pos_x; int pos_y; int width; int height; int offset; int scr_width; int bpp; int /*<<< orphan*/  color_mode; } ;
struct TYPE_9__ {int flags; } ;
struct TYPE_10__ {TYPE_3__ update; } ;
struct blizzard_request {TYPE_4__ par; } ;
struct TYPE_12__ {int enabled_planes; int last_color_mode; int screen_height; int zoom_on; int screen_width; int zoom_area_gx1; int zoom_area_gx2; int zoom_area_gy1; int zoom_area_gy2; TYPE_2__* extif; TYPE_5__* int_ctrl; TYPE_1__* fbdev; struct plane_info* plane; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* enable_plane ) (int,int) ;int /*<<< orphan*/  (* setup_plane ) (int,int /*<<< orphan*/ ,unsigned long,int,int,int,int,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  (* transfer_area ) (int,int,int /*<<< orphan*/ ,struct blizzard_request*) ;int /*<<< orphan*/  (* set_bits_per_cycle ) (int) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BLIZZARD_COLOR_RGB565 ; 
 int BLIZZARD_COLOR_YUV420 ; 
 int /*<<< orphan*/  OMAPFB_CHANNEL_OUT_LCD ; 
#define  OMAPFB_COLOR_YUV420 128 
 int OMAPFB_FORMAT_FLAG_DOUBLE ; 
 int OMAPFB_FORMAT_FLAG_FORCE_VSYNC ; 
 int OMAPFB_FORMAT_FLAG_TEARSYNC ; 
 int OMAPFB_PLANE_NUM ; 
 int REQ_PENDING ; 
 TYPE_6__ blizzard ; 
 int /*<<< orphan*/  blizzard_wait_line_buffer () ; 
 int /*<<< orphan*/  blizzard_wait_yyc () ; 
 scalar_t__ check_1d_intersect (int,int,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned long,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  disable_tearsync () ; 
 int /*<<< orphan*/  enable_tearsync (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  request_complete ; 
 int /*<<< orphan*/  set_window_regs (int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub1 (int,int) ; 
 int /*<<< orphan*/  stub2 (int,int) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ,unsigned long,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int) ; 
 int /*<<< orphan*/  stub5 (int) ; 
 int /*<<< orphan*/  stub6 (int,int,int /*<<< orphan*/ ,struct blizzard_request*) ; 

__attribute__((used)) static int do_partial_update(struct blizzard_request *req, int plane,
			     int x, int y, int w, int h,
			     int x_out, int y_out, int w_out, int h_out,
			     int wnd_color_mode, int bpp)
{
	int i;
	int gx1, gy1, gx2, gy2;
	int gx1_out, gy1_out, gx2_out, gy2_out;
	int color_mode;
	int flags;
	int zoom_off;
	int have_zoom_for_this_update = 0;

	/* Global coordinates, relative to pixel 0,0 of the LCD */
	gx1 = x + blizzard.plane[plane].pos_x;
	gy1 = y + blizzard.plane[plane].pos_y;
	gx2 = gx1 + w;
	gy2 = gy1 + h;

	flags = req->par.update.flags;
	if (flags & OMAPFB_FORMAT_FLAG_DOUBLE) {
		gx1_out = gx1;
		gy1_out = gy1;
		gx2_out = gx1 + w * 2;
		gy2_out = gy1 + h * 2;
	} else {
		gx1_out = x_out + blizzard.plane[plane].pos_x;
		gy1_out = y_out + blizzard.plane[plane].pos_y;
		gx2_out = gx1_out + w_out;
		gy2_out = gy1_out + h_out;
	}

	for (i = 0; i < OMAPFB_PLANE_NUM; i++) {
		struct plane_info *p = &blizzard.plane[i];
		int px1, py1;
		int px2, py2;
		int pw, ph;
		int pposx, pposy;
		unsigned long offset;

		if (!(blizzard.enabled_planes & (1 << i))  ||
		    (wnd_color_mode && i != plane)) {
			blizzard.int_ctrl->enable_plane(i, 0);
			continue;
		}
		/* Plane coordinates */
		if (i == plane) {
			/* Plane in which we are doing the update.
			 * Local coordinates are the one in the update
			 * request.
			 */
			px1 = x;
			py1 = y;
			px2 = x + w;
			py2 = y + h;
			pposx = 0;
			pposy = 0;
		} else {
			/* Check if this plane has an overlapping part */
			px1 = gx1 - p->pos_x;
			py1 = gy1 - p->pos_y;
			px2 = gx2 - p->pos_x;
			py2 = gy2 - p->pos_y;
			if (px1 >= p->width || py1 >= p->height ||
			    px2 <= 0 || py2 <= 0) {
				blizzard.int_ctrl->enable_plane(i, 0);
				continue;
			}
			/* Calculate the coordinates for the overlapping
			 * part in the plane's local coordinates.
			 */
			pposx = -px1;
			pposy = -py1;
			if (px1 < 0)
				px1 = 0;
			if (py1 < 0)
				py1 = 0;
			if (px2 > p->width)
				px2 = p->width;
			if (py2 > p->height)
				py2 = p->height;
			if (pposx < 0)
				pposx = 0;
			if (pposy < 0)
				pposy = 0;
		}
		pw = px2 - px1;
		ph = py2 - py1;
		offset = p->offset + (p->scr_width * py1 + px1) * p->bpp / 8;
		if (wnd_color_mode)
			/* Window embedded in the plane with a differing
			 * color mode / bpp. Calculate the number of DMA
			 * transfer elements in terms of the plane's bpp.
			 */
			pw = (pw + 1) * bpp / p->bpp;
#ifdef VERBOSE
		dev_dbg(blizzard.fbdev->dev,
			"plane %d offset %#08lx pposx %d pposy %d "
			"px1 %d py1 %d pw %d ph %d\n",
			i, offset, pposx, pposy, px1, py1, pw, ph);
#endif
		blizzard.int_ctrl->setup_plane(i,
				OMAPFB_CHANNEL_OUT_LCD, offset,
				p->scr_width,
				pposx, pposy, pw, ph,
				p->color_mode);

		blizzard.int_ctrl->enable_plane(i, 1);
	}

	switch (wnd_color_mode) {
	case OMAPFB_COLOR_YUV420:
		color_mode = BLIZZARD_COLOR_YUV420;
		/* Currently only the 16 bits/pixel cycle format is
		 * supported on the external interface. Adjust the number
		 * of transfer elements per line for 12bpp format.
		 */
		w = (w + 1) * 3 / 4;
		break;
	default:
		color_mode = BLIZZARD_COLOR_RGB565;
		break;
	}

	blizzard_wait_line_buffer();
	if (blizzard.last_color_mode == BLIZZARD_COLOR_YUV420)
		blizzard_wait_yyc();
	blizzard.last_color_mode = color_mode;
	if (flags & OMAPFB_FORMAT_FLAG_TEARSYNC)
		enable_tearsync(gy1, w, h,
				blizzard.screen_height,
				h_out,
				flags & OMAPFB_FORMAT_FLAG_FORCE_VSYNC);
	else
		disable_tearsync();

	if ((gx2_out - gx1_out) != (gx2 - gx1) ||
	    (gy2_out - gy1_out) != (gy2 - gy1))
		have_zoom_for_this_update = 1;

	/* 'background' type of screen update (as opposed to 'destructive')
	   can be used to disable scaling if scaling is active */
	zoom_off = blizzard.zoom_on && !have_zoom_for_this_update &&
	    (gx1_out == 0) && (gx2_out == blizzard.screen_width) &&
	    (gy1_out == 0) && (gy2_out == blizzard.screen_height) &&
	    (gx1 == 0) && (gy1 == 0);

	if (blizzard.zoom_on && !have_zoom_for_this_update && !zoom_off &&
	    check_1d_intersect(blizzard.zoom_area_gx1, blizzard.zoom_area_gx2,
			       gx1_out, gx2_out) &&
	    check_1d_intersect(blizzard.zoom_area_gy1, blizzard.zoom_area_gy2,
			       gy1_out, gy2_out)) {
		/* Previous screen update was using scaling, current update
		 * is not using it. Additionally, current screen update is
		 * going to overlap with the scaled area. Scaling needs to be
		 * disabled in order to avoid 'magnifying glass' effect.
		 * Dummy setup of background window can be used for this.
		 */
		set_window_regs(0, 0, blizzard.screen_width,
				blizzard.screen_height,
				0, 0, blizzard.screen_width,
				blizzard.screen_height,
				BLIZZARD_COLOR_RGB565, 1, flags);
		blizzard.zoom_on = 0;
	}

	/* remember scaling settings if we have scaled update */
	if (have_zoom_for_this_update) {
		blizzard.zoom_on = 1;
		blizzard.zoom_area_gx1 = gx1_out;
		blizzard.zoom_area_gx2 = gx2_out;
		blizzard.zoom_area_gy1 = gy1_out;
		blizzard.zoom_area_gy2 = gy2_out;
	}

	set_window_regs(gx1, gy1, gx2, gy2, gx1_out, gy1_out, gx2_out, gy2_out,
			color_mode, zoom_off, flags);
	if (zoom_off)
		blizzard.zoom_on = 0;

	blizzard.extif->set_bits_per_cycle(16);
	/* set_window_regs has left the register index at the right
	 * place, so no need to set it here.
	 */
	blizzard.extif->transfer_area(w, h, request_complete, req);

	return REQ_PENDING;
}