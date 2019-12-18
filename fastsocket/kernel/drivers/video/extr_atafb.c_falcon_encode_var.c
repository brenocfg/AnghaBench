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
struct TYPE_8__ {scalar_t__ msb_right; scalar_t__ length; scalar_t__ offset; } ;
struct TYPE_7__ {int offset; int length; scalar_t__ msb_right; } ;
struct fb_var_screeninfo {int pixclock; int height; int width; int vmode; int yres; int bits_per_pixel; int xres; int xres_virtual; int yres_virtual; int left_margin; int right_margin; int hsync_len; int upper_margin; int lower_margin; int vsync_len; int yoffset; scalar_t__ activate; scalar_t__ nonstd; scalar_t__ xoffset; TYPE_2__ transp; TYPE_1__ red; TYPE_1__ green; TYPE_1__ blue; scalar_t__ grayscale; int /*<<< orphan*/  sync; } ;
struct falcon_hw {int sync; int vid_control; int vid_mode; int vde; int vdb; int f_shift; int st_shift; int line_width; int line_offset; int hdb; int hht; int hde; int hbb; int hss; int vft; int vss; scalar_t__ ste_mode; scalar_t__ xoffset; } ;
struct TYPE_9__ {struct falcon_hw falcon; } ;
struct atafb_par {int yres_virtual; int screen_base; TYPE_3__ hw; } ;
struct TYPE_12__ {int t; } ;
struct TYPE_11__ {int t; } ;
struct TYPE_10__ {int t; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_SYNC_HOR_HIGH_ACT ; 
 int /*<<< orphan*/  FB_SYNC_VERT_HIGH_ACT ; 
 int FB_VMODE_DOUBLE ; 
 int FB_VMODE_INTERLACED ; 
 int FB_VMODE_NONINTERLACED ; 
 scalar_t__ F_MON_VGA ; 
 int VCO_CLOCK25 ; 
 int VCO_HSYPOS ; 
 int VCO_SHORTOFFS ; 
 int VCO_VSYPOS ; 
 int VMO_DOUBLE ; 
 int VMO_INTER ; 
 TYPE_6__ f25 ; 
 TYPE_5__ f32 ; 
 TYPE_4__ fext ; 
 int hwscroll ; 
 int hxx_prescale (struct falcon_hw*) ; 
 int /*<<< orphan*/  memset (struct fb_var_screeninfo*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mon_type ; 
 int screen_base ; 
 int screen_len ; 

__attribute__((used)) static int falcon_encode_var(struct fb_var_screeninfo *var,
			     struct atafb_par *par)
{
/* !!! only for VGA !!! */
	int linelen;
	int prescale, plen;
	int hdb_off, hde_off, base_off;
	struct falcon_hw *hw = &par->hw.falcon;

	memset(var, 0, sizeof(struct fb_var_screeninfo));
	/* possible frequencies: 25.175 or 32MHz */
	var->pixclock = hw->sync & 0x1 ? fext.t :
	                hw->vid_control & VCO_CLOCK25 ? f25.t : f32.t;

	var->height = -1;
	var->width = -1;

	var->sync = 0;
	if (hw->vid_control & VCO_HSYPOS)
		var->sync |= FB_SYNC_HOR_HIGH_ACT;
	if (hw->vid_control & VCO_VSYPOS)
		var->sync |= FB_SYNC_VERT_HIGH_ACT;

	var->vmode = FB_VMODE_NONINTERLACED;
	if (hw->vid_mode & VMO_INTER)
		var->vmode |= FB_VMODE_INTERLACED;
	if (hw->vid_mode & VMO_DOUBLE)
		var->vmode |= FB_VMODE_DOUBLE;

	/* visible y resolution:
	 * Graphics display starts at line VDB and ends at line
	 * VDE. If interlace mode off unit of VC-registers is
	 * half lines, else lines.
	 */
	var->yres = hw->vde - hw->vdb;
	if (!(var->vmode & FB_VMODE_INTERLACED))
		var->yres >>= 1;
	if (var->vmode & FB_VMODE_DOUBLE)
		var->yres >>= 1;

	/*
	 * to get bpp, we must examine f_shift and st_shift.
	 * f_shift is valid if any of bits no. 10, 8 or 4
	 * is set. Priority in f_shift is: 10 ">" 8 ">" 4, i.e.
	 * if bit 10 set then bit 8 and bit 4 don't care...
	 * If all these bits are 0 get display depth from st_shift
	 * (as for ST and STE)
	 */
	if (hw->f_shift & 0x400)	/* 2 colors */
		var->bits_per_pixel = 1;
	else if (hw->f_shift & 0x100)	/* hicolor */
		var->bits_per_pixel = 16;
	else if (hw->f_shift & 0x010)	/* 8 bitplanes */
		var->bits_per_pixel = 8;
	else if (hw->st_shift == 0)
		var->bits_per_pixel = 4;
	else if (hw->st_shift == 0x100)
		var->bits_per_pixel = 2;
	else				/* if (hw->st_shift == 0x200) */
		var->bits_per_pixel = 1;

	var->xres = hw->line_width * 16 / var->bits_per_pixel;
	var->xres_virtual = var->xres + hw->line_offset * 16 / var->bits_per_pixel;
	if (hw->xoffset)
		var->xres_virtual += 16;

	if (var->bits_per_pixel == 16) {
		var->red.offset = 11;
		var->red.length = 5;
		var->red.msb_right = 0;
		var->green.offset = 5;
		var->green.length = 6;
		var->green.msb_right = 0;
		var->blue.offset = 0;
		var->blue.length = 5;
		var->blue.msb_right = 0;
	} else {
		var->red.offset = 0;
		var->red.length = hw->ste_mode ? 4 : 6;
		if (var->red.length > var->bits_per_pixel)
			var->red.length = var->bits_per_pixel;
		var->red.msb_right = 0;
		var->grayscale = 0;
		var->blue = var->green = var->red;
	}
	var->transp.offset = 0;
	var->transp.length = 0;
	var->transp.msb_right = 0;

	linelen = var->xres_virtual * var->bits_per_pixel / 8;
	if (screen_len) {
		if (par->yres_virtual)
			var->yres_virtual = par->yres_virtual;
		else
			/* yres_virtual == 0 means use maximum */
			var->yres_virtual = screen_len / linelen;
	} else {
		if (hwscroll < 0)
			var->yres_virtual = 2 * var->yres;
		else
			var->yres_virtual = var->yres + hwscroll * 16;
	}
	var->xoffset = 0;		/* TODO change this */

	/* hdX-offsets */
	prescale = hxx_prescale(hw);
	plen = 4 >> (hw->vid_mode >> 2 & 0x3);
	base_off = hw->vid_control & VCO_SHORTOFFS ? 64 : 128;
	if (hw->f_shift & 0x100) {
		hde_off = 0;
		hdb_off = (base_off + 16 * plen) + prescale;
	} else {
		hde_off = ((128 / var->bits_per_pixel + 2) * plen);
		if (hw->ste_mode)
			hdb_off = (64 + base_off + (128 / var->bits_per_pixel + 2) * plen)
					 + prescale;
		else
			hdb_off = (base_off + (128 / var->bits_per_pixel + 18) * plen)
					 + prescale;
	}

	/* Right margin includes hsync */
	var->left_margin = hdb_off + prescale * ((hw->hdb & 0x1ff) -
					   (hw->hdb & 0x200 ? 2 + hw->hht : 0));
	if (hw->ste_mode || mon_type != F_MON_VGA)
		var->right_margin = prescale * (hw->hht + 2 - hw->hde) - hde_off;
	else
		/* can't use this in ste_mode, because hbb is +1 off */
		var->right_margin = prescale * (hw->hht + 2 - hw->hbb);
	var->hsync_len = prescale * (hw->hht + 2 - hw->hss);

	/* Lower margin includes vsync */
	var->upper_margin = hw->vdb / 2;	/* round down to full lines */
	var->lower_margin = (hw->vft + 1 - hw->vde + 1) / 2;	/* round up */
	var->vsync_len = (hw->vft + 1 - hw->vss + 1) / 2;	/* round up */
	if (var->vmode & FB_VMODE_INTERLACED) {
		var->upper_margin *= 2;
		var->lower_margin *= 2;
		var->vsync_len *= 2;
	} else if (var->vmode & FB_VMODE_DOUBLE) {
		var->upper_margin = (var->upper_margin + 1) / 2;
		var->lower_margin = (var->lower_margin + 1) / 2;
		var->vsync_len = (var->vsync_len + 1) / 2;
	}

	var->pixclock *= plen;
	var->left_margin /= plen;
	var->right_margin /= plen;
	var->hsync_len /= plen;

	var->right_margin -= var->hsync_len;
	var->lower_margin -= var->vsync_len;

	if (screen_base)
		var->yoffset = (par->screen_base - screen_base) / linelen;
	else
		var->yoffset = 0;
	var->nonstd = 0;		/* what is this for? */
	var->activate = 0;
	return 0;
}