#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int length; int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {int offset; int length; } ;
struct TYPE_4__ {int offset; int length; } ;
struct fb_var_screeninfo {int bits_per_pixel; scalar_t__ vsync_len; scalar_t__ lower_margin; scalar_t__ upper_margin; scalar_t__ hsync_len; scalar_t__ right_margin; scalar_t__ left_margin; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; int /*<<< orphan*/  pixclock; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; } ;
struct display_timing {scalar_t__ ver_sync_end; scalar_t__ ver_addr; scalar_t__ ver_sync_start; scalar_t__ ver_total; scalar_t__ hor_sync_end; scalar_t__ hor_addr; scalar_t__ hor_sync_start; scalar_t__ hor_total; } ;
struct crt_mode_table {int refresh_rate; struct display_timing crtc; } ;
struct VideoModeTable {int mode_array; struct crt_mode_table* crtc; } ;

/* Variables and functions */
 struct VideoModeTable* CLE266Modes ; 
 size_t search_mode_setting (int) ; 
 int /*<<< orphan*/  viafb_get_pixclock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void viafb_fill_var_timing_info(struct fb_var_screeninfo *var, int refresh,
			  int mode_index)
{
	struct VideoModeTable *vmode_tbl = NULL;
	struct crt_mode_table *crt_timing = NULL;
	struct display_timing crt_reg;
	int i = 0, index = 0;
	vmode_tbl = &CLE266Modes[search_mode_setting(mode_index)];
	crt_timing = vmode_tbl->crtc;
	for (i = 0; i < vmode_tbl->mode_array; i++) {
		index = i;
		if (crt_timing[i].refresh_rate == refresh)
			break;
	}

	crt_reg = crt_timing[index].crtc;
	switch (var->bits_per_pixel) {
	case 8:
		var->red.offset = 0;
		var->green.offset = 0;
		var->blue.offset = 0;
		var->red.length = 6;
		var->green.length = 6;
		var->blue.length = 6;
		break;
	case 16:
		var->red.offset = 11;
		var->green.offset = 5;
		var->blue.offset = 0;
		var->red.length = 5;
		var->green.length = 6;
		var->blue.length = 5;
		break;
	case 32:
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		break;
	default:
		/* never happed, put here to keep consistent */
		break;
	}

	var->pixclock = viafb_get_pixclock(var->xres, var->yres, refresh);
	var->left_margin =
	    crt_reg.hor_total - (crt_reg.hor_sync_start + crt_reg.hor_sync_end);
	var->right_margin = crt_reg.hor_sync_start - crt_reg.hor_addr;
	var->hsync_len = crt_reg.hor_sync_end;
	var->upper_margin =
	    crt_reg.ver_total - (crt_reg.ver_sync_start + crt_reg.ver_sync_end);
	var->lower_margin = crt_reg.ver_sync_start - crt_reg.ver_addr;
	var->vsync_len = crt_reg.ver_sync_end;
}