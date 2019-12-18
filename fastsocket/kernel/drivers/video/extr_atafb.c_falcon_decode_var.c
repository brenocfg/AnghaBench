#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pixel_clock {int t; int hsync; int right; int left; int f; int control_mask; int sync_mask; } ;
struct fb_var_screeninfo {int bits_per_pixel; int xres; int yres; int xres_virtual; int yres_virtual; int pixclock; int left_margin; int right_margin; int hsync_len; int upper_margin; int lower_margin; int vsync_len; int vmode; int sync; int yoffset; } ;
struct TYPE_8__ {int f_shift; int st_shift; int bpp; int ste_mode; int mono; int line_width; int line_offset; int vid_control; int sync; int vid_mode; scalar_t__ xoffset; } ;
struct TYPE_7__ {TYPE_3__ falcon; } ;
struct atafb_par {int HHT; int HDB; int HBE; int HDE; int HBB; int HSS; int VBE; int VDB; int VDE; int VBB; int VFT; int VSS; int yres_virtual; int next_line; TYPE_2__ hw; scalar_t__ screen_base; } ;
struct TYPE_6__ {int hfmin; int hfmax; int vfmax; int vfmin; } ;
struct TYPE_10__ {TYPE_1__ monspecs; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* get_par ) (struct atafb_par*) ;} ;

/* Variables and functions */
 scalar_t__ DontCalcRes ; 
 int EINVAL ; 
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int FB_VMODE_DOUBLE ; 
 int FB_VMODE_INTERLACED ; 
 int F_MON_SC ; 
 int F_MON_SM ; 
 int F_MON_TV ; 
 int F_MON_VGA ; 
 unsigned long ULONG_MAX ; 
 int VCO_HSYPOS ; 
 int VCO_SHORTOFFS ; 
 int VCO_VSYPOS ; 
 int VMO_DOUBLE ; 
 int VMO_INTER ; 
 struct fb_var_screeninfo* atafb_predefined ; 
 int f030_bus_width ; 
 struct pixel_clock f25 ; 
 struct pixel_clock f32 ; 
 TYPE_5__ fb_info ; 
 TYPE_4__* fbhw ; 
 struct pixel_clock fext ; 
 int hxx_prescale (TYPE_3__*) ; 
 int mon_type ; 
 int roundup (int,int) ; 
 scalar_t__ screen_base ; 
 int screen_len ; 
 int /*<<< orphan*/  stub1 (struct atafb_par*) ; 

__attribute__((used)) static int falcon_decode_var(struct fb_var_screeninfo *var,
			     struct atafb_par *par)
{
	int bpp = var->bits_per_pixel;
	int xres = var->xres;
	int yres = var->yres;
	int xres_virtual = var->xres_virtual;
	int yres_virtual = var->yres_virtual;
	int left_margin, right_margin, hsync_len;
	int upper_margin, lower_margin, vsync_len;
	int linelen;
	int interlace = 0, doubleline = 0;
	struct pixel_clock *pclock;
	int plen;			/* width of pixel in clock cycles */
	int xstretch;
	int prescale;
	int longoffset = 0;
	int hfreq, vfreq;
	int hdb_off, hde_off, base_off;
	int gstart, gend1, gend2, align;

/*
	Get the video params out of 'var'. If a value doesn't fit, round
	it up, if it's too big, return EINVAL.
	Round up in the following order: bits_per_pixel, xres, yres,
	xres_virtual, yres_virtual, xoffset, yoffset, grayscale, bitfields,
	horizontal timing, vertical timing.

	There is a maximum of screen resolution determined by pixelclock
	and minimum frame rate -- (X+hmarg.)*(Y+vmarg.)*vfmin <= pixelclock.
	In interlace mode this is     "     *    "     *vfmin <= pixelclock.
	Additional constraints: hfreq.
	Frequency range for multisync monitors is given via command line.
	For TV and SM124 both frequencies are fixed.

	X % 16 == 0 to fit 8x?? font (except 1 bitplane modes must use X%32 == 0)
	Y % 16 == 0 to fit 8x16 font
	Y % 8 == 0 if Y<400

	Currently interlace and doubleline mode in var are ignored.
	On SM124 and TV only the standard resolutions can be used.
*/

	/* Reject uninitialized mode */
	if (!xres || !yres || !bpp)
		return -EINVAL;

	if (mon_type == F_MON_SM && bpp != 1)
		return -EINVAL;

	if (bpp <= 1) {
		bpp = 1;
		par->hw.falcon.f_shift = 0x400;
		par->hw.falcon.st_shift = 0x200;
	} else if (bpp <= 2) {
		bpp = 2;
		par->hw.falcon.f_shift = 0x000;
		par->hw.falcon.st_shift = 0x100;
	} else if (bpp <= 4) {
		bpp = 4;
		par->hw.falcon.f_shift = 0x000;
		par->hw.falcon.st_shift = 0x000;
	} else if (bpp <= 8) {
		bpp = 8;
		par->hw.falcon.f_shift = 0x010;
	} else if (bpp <= 16) {
		bpp = 16;		/* packed pixel mode */
		par->hw.falcon.f_shift = 0x100;	/* hicolor, no overlay */
	} else
		return -EINVAL;
	par->hw.falcon.bpp = bpp;

	if (mon_type == F_MON_SM || DontCalcRes) {
		/* Skip all calculations. VGA/TV/SC1224 only supported. */
		struct fb_var_screeninfo *myvar = &atafb_predefined[0];

		if (bpp > myvar->bits_per_pixel ||
		    var->xres > myvar->xres ||
		    var->yres > myvar->yres)
			return -EINVAL;
		fbhw->get_par(par);	/* Current par will be new par */
		goto set_screen_base;	/* Don't forget this */
	}

	/* Only some fixed resolutions < 640x400 */
	if (xres <= 320)
		xres = 320;
	else if (xres <= 640 && bpp != 16)
		xres = 640;
	if (yres <= 200)
		yres = 200;
	else if (yres <= 240)
		yres = 240;
	else if (yres <= 400)
		yres = 400;

	/* 2 planes must use STE compatibility mode */
	par->hw.falcon.ste_mode = bpp == 2;
	par->hw.falcon.mono = bpp == 1;

	/* Total and visible scanline length must be a multiple of one longword,
	 * this and the console fontwidth yields the alignment for xres and
	 * xres_virtual.
	 * TODO: this way "odd" fontheights are not supported
	 *
	 * Special case in STE mode: blank and graphic positions don't align,
	 * avoid trash at right margin
	 */
	if (par->hw.falcon.ste_mode)
		xres = (xres + 63) & ~63;
	else if (bpp == 1)
		xres = (xres + 31) & ~31;
	else
		xres = (xres + 15) & ~15;
	if (yres >= 400)
		yres = (yres + 15) & ~15;
	else
		yres = (yres + 7) & ~7;

	if (xres_virtual < xres)
		xres_virtual = xres;
	else if (bpp == 1)
		xres_virtual = (xres_virtual + 31) & ~31;
	else
		xres_virtual = (xres_virtual + 15) & ~15;

	if (yres_virtual <= 0)
		yres_virtual = 0;
	else if (yres_virtual < yres)
		yres_virtual = yres;

	/* backward bug-compatibility */
	if (var->pixclock > 1)
		var->pixclock -= 1;

	par->hw.falcon.line_width = bpp * xres / 16;
	par->hw.falcon.line_offset = bpp * (xres_virtual - xres) / 16;

	/* single or double pixel width */
	xstretch = (xres < 640) ? 2 : 1;

#if 0 /* SM124 supports only 640x400, this is rejected above */
	if (mon_type == F_MON_SM) {
		if (xres != 640 && yres != 400)
			return -EINVAL;
		plen = 1;
		pclock = &f32;
		/* SM124-mode is special */
		par->hw.falcon.ste_mode = 1;
		par->hw.falcon.f_shift = 0x000;
		par->hw.falcon.st_shift = 0x200;
		left_margin = hsync_len = 128 / plen;
		right_margin = 0;
		/* TODO set all margins */
	} else
#endif
	if (mon_type == F_MON_SC || mon_type == F_MON_TV) {
		plen = 2 * xstretch;
		if (var->pixclock > f32.t * plen)
			return -EINVAL;
		pclock = &f32;
		if (yres > 240)
			interlace = 1;
		if (var->pixclock == 0) {
			/* set some minimal margins which center the screen */
			left_margin = 32;
			right_margin = 18;
			hsync_len = pclock->hsync / plen;
			upper_margin = 31;
			lower_margin = 14;
			vsync_len = interlace ? 3 : 4;
		} else {
			left_margin = var->left_margin;
			right_margin = var->right_margin;
			hsync_len = var->hsync_len;
			upper_margin = var->upper_margin;
			lower_margin = var->lower_margin;
			vsync_len = var->vsync_len;
			if (var->vmode & FB_VMODE_INTERLACED) {
				upper_margin = (upper_margin + 1) / 2;
				lower_margin = (lower_margin + 1) / 2;
				vsync_len = (vsync_len + 1) / 2;
			} else if (var->vmode & FB_VMODE_DOUBLE) {
				upper_margin *= 2;
				lower_margin *= 2;
				vsync_len *= 2;
			}
		}
	} else {			/* F_MON_VGA */
		if (bpp == 16)
			xstretch = 2;	/* Double pixel width only for hicolor */
		/* Default values are used for vert./hor. timing if no pixelclock given. */
		if (var->pixclock == 0) {
			int linesize;

			/* Choose master pixelclock depending on hor. timing */
			plen = 1 * xstretch;
			if ((plen * xres + f25.right + f25.hsync + f25.left) *
			    fb_info.monspecs.hfmin < f25.f)
				pclock = &f25;
			else if ((plen * xres + f32.right + f32.hsync +
				  f32.left) * fb_info.monspecs.hfmin < f32.f)
				pclock = &f32;
			else if ((plen * xres + fext.right + fext.hsync +
				  fext.left) * fb_info.monspecs.hfmin < fext.f &&
			         fext.f)
				pclock = &fext;
			else
				return -EINVAL;

			left_margin = pclock->left / plen;
			right_margin = pclock->right / plen;
			hsync_len = pclock->hsync / plen;
			linesize = left_margin + xres + right_margin + hsync_len;
			upper_margin = 31;
			lower_margin = 11;
			vsync_len = 3;
		} else {
			/* Choose largest pixelclock <= wanted clock */
			int i;
			unsigned long pcl = ULONG_MAX;
			pclock = 0;
			for (i = 1; i <= 4; i *= 2) {
				if (f25.t * i >= var->pixclock &&
				    f25.t * i < pcl) {
					pcl = f25.t * i;
					pclock = &f25;
				}
				if (f32.t * i >= var->pixclock &&
				    f32.t * i < pcl) {
					pcl = f32.t * i;
					pclock = &f32;
				}
				if (fext.t && fext.t * i >= var->pixclock &&
				    fext.t * i < pcl) {
					pcl = fext.t * i;
					pclock = &fext;
				}
			}
			if (!pclock)
				return -EINVAL;
			plen = pcl / pclock->t;

			left_margin = var->left_margin;
			right_margin = var->right_margin;
			hsync_len = var->hsync_len;
			upper_margin = var->upper_margin;
			lower_margin = var->lower_margin;
			vsync_len = var->vsync_len;
			/* Internal unit is [single lines per (half-)frame] */
			if (var->vmode & FB_VMODE_INTERLACED) {
				/* # lines in half frame */
				/* External unit is [lines per full frame] */
				upper_margin = (upper_margin + 1) / 2;
				lower_margin = (lower_margin + 1) / 2;
				vsync_len = (vsync_len + 1) / 2;
			} else if (var->vmode & FB_VMODE_DOUBLE) {
				/* External unit is [double lines per frame] */
				upper_margin *= 2;
				lower_margin *= 2;
				vsync_len *= 2;
			}
		}
		if (pclock == &fext)
			longoffset = 1;	/* VIDEL doesn't synchronize on short offset */
	}
	/* Is video bus bandwidth (32MB/s) too low for this resolution? */
	/* this is definitely wrong if bus clock != 32MHz */
	if (pclock->f / plen / 8 * bpp > 32000000L)
		return -EINVAL;

	if (vsync_len < 1)
		vsync_len = 1;

	/* include sync lengths in right/lower margin for all calculations */
	right_margin += hsync_len;
	lower_margin += vsync_len;

	/* ! In all calculations of margins we use # of lines in half frame
	 * (which is a full frame in non-interlace mode), so we can switch
	 * between interlace and non-interlace without messing around
	 * with these.
	 */
again:
	/* Set base_offset 128 and video bus width */
	par->hw.falcon.vid_control = mon_type | f030_bus_width;
	if (!longoffset)
		par->hw.falcon.vid_control |= VCO_SHORTOFFS;	/* base_offset 64 */
	if (var->sync & FB_SYNC_HOR_HIGH_ACT)
		par->hw.falcon.vid_control |= VCO_HSYPOS;
	if (var->sync & FB_SYNC_VERT_HIGH_ACT)
		par->hw.falcon.vid_control |= VCO_VSYPOS;
	/* Pixelclock */
	par->hw.falcon.vid_control |= pclock->control_mask;
	/* External or internal clock */
	par->hw.falcon.sync = pclock->sync_mask | 0x2;
	/* Pixellength and prescale */
	par->hw.falcon.vid_mode = (2 / plen) << 2;
	if (doubleline)
		par->hw.falcon.vid_mode |= VMO_DOUBLE;
	if (interlace)
		par->hw.falcon.vid_mode |= VMO_INTER;

	/*********************
	 * Horizontal timing: unit = [master clock cycles]
	 * unit of hxx-registers: [master clock cycles * prescale]
	 * Hxx-registers are 9 bit wide
	 *
	 * 1 line = ((hht + 2) * 2 * prescale) clock cycles
	 *
	 * graphic output = hdb & 0x200 ?
	 *        ((hht + 2) * 2 - hdb + hde) * prescale - hdboff + hdeoff:
	 *        (hht + 2  - hdb + hde) * prescale - hdboff + hdeoff
	 * (this must be a multiple of plen*128/bpp, on VGA pixels
	 *  to the right may be cut off with a bigger right margin)
	 *
	 * start of graphics relative to start of 1st halfline = hdb & 0x200 ?
	 *        (hdb - hht - 2) * prescale + hdboff :
	 *        hdb * prescale + hdboff
	 *
	 * end of graphics relative to start of 1st halfline =
	 *        (hde + hht + 2) * prescale + hdeoff
	 *********************/
	/* Calculate VIDEL registers */
{
	prescale = hxx_prescale(&par->hw.falcon);
	base_off = par->hw.falcon.vid_control & VCO_SHORTOFFS ? 64 : 128;

	/* Offsets depend on video mode */
	/* Offsets are in clock cycles, divide by prescale to
	 * calculate hd[be]-registers
	 */
	if (par->hw.falcon.f_shift & 0x100) {
		align = 1;
		hde_off = 0;
		hdb_off = (base_off + 16 * plen) + prescale;
	} else {
		align = 128 / bpp;
		hde_off = ((128 / bpp + 2) * plen);
		if (par->hw.falcon.ste_mode)
			hdb_off = (64 + base_off + (128 / bpp + 2) * plen) + prescale;
		else
			hdb_off = (base_off + (128 / bpp + 18) * plen) + prescale;
	}

	gstart = (prescale / 2 + plen * left_margin) / prescale;
	/* gend1 is for hde (gend-gstart multiple of align), shifter's xres */
	gend1 = gstart + roundup(xres, align) * plen / prescale;
	/* gend2 is for hbb, visible xres (rest to gend1 is cut off by hblank) */
	gend2 = gstart + xres * plen / prescale;
	par->HHT = plen * (left_margin + xres + right_margin) /
			   (2 * prescale) - 2;
/*	par->HHT = (gend2 + plen * right_margin / prescale) / 2 - 2;*/

	par->HDB = gstart - hdb_off / prescale;
	par->HBE = gstart;
	if (par->HDB < 0)
		par->HDB += par->HHT + 2 + 0x200;
	par->HDE = gend1 - par->HHT - 2 - hde_off / prescale;
	par->HBB = gend2 - par->HHT - 2;
#if 0
	/* One more Videl constraint: data fetch of two lines must not overlap */
	if ((par->HDB & 0x200) && (par->HDB & ~0x200) - par->HDE <= 5) {
		/* if this happens increase margins, decrease hfreq. */
	}
#endif
	if (hde_off % prescale)
		par->HBB++;		/* compensate for non matching hde and hbb */
	par->HSS = par->HHT + 2 - plen * hsync_len / prescale;
	if (par->HSS < par->HBB)
		par->HSS = par->HBB;
}

	/*  check hor. frequency */
	hfreq = pclock->f / ((par->HHT + 2) * prescale * 2);
	if (hfreq > fb_info.monspecs.hfmax && mon_type != F_MON_VGA) {
		/* ++guenther:   ^^^^^^^^^^^^^^^^^^^ can't remember why I did this */
		/* Too high -> enlarge margin */
		left_margin += 1;
		right_margin += 1;
		goto again;
	}
	if (hfreq > fb_info.monspecs.hfmax || hfreq < fb_info.monspecs.hfmin)
		return -EINVAL;

	/* Vxx-registers */
	/* All Vxx must be odd in non-interlace, since frame starts in the middle
	 * of the first displayed line!
	 * One frame consists of VFT+1 half lines. VFT+1 must be even in
	 * non-interlace, odd in interlace mode for synchronisation.
	 * Vxx-registers are 11 bit wide
	 */
	par->VBE = (upper_margin * 2 + 1); /* must begin on odd halfline */
	par->VDB = par->VBE;
	par->VDE = yres;
	if (!interlace)
		par->VDE <<= 1;
	if (doubleline)
		par->VDE <<= 1;		/* VDE now half lines per (half-)frame */
	par->VDE += par->VDB;
	par->VBB = par->VDE;
	par->VFT = par->VBB + (lower_margin * 2 - 1) - 1;
	par->VSS = par->VFT + 1 - (vsync_len * 2 - 1);
	/* vbb,vss,vft must be even in interlace mode */
	if (interlace) {
		par->VBB++;
		par->VSS++;
		par->VFT++;
	}

	/* V-frequency check, hope I didn't create any loop here. */
	/* Interlace and doubleline are mutually exclusive. */
	vfreq = (hfreq * 2) / (par->VFT + 1);
	if (vfreq > fb_info.monspecs.vfmax && !doubleline && !interlace) {
		/* Too high -> try again with doubleline */
		doubleline = 1;
		goto again;
	} else if (vfreq < fb_info.monspecs.vfmin && !interlace && !doubleline) {
		/* Too low -> try again with interlace */
		interlace = 1;
		goto again;
	} else if (vfreq < fb_info.monspecs.vfmin && doubleline) {
		/* Doubleline too low -> clear doubleline and enlarge margins */
		int lines;
		doubleline = 0;
		for (lines = 0;
		     (hfreq * 2) / (par->VFT + 1 + 4 * lines - 2 * yres) >
		     fb_info.monspecs.vfmax;
		     lines++)
			;
		upper_margin += lines;
		lower_margin += lines;
		goto again;
	} else if (vfreq > fb_info.monspecs.vfmax && doubleline) {
		/* Doubleline too high -> enlarge margins */
		int lines;
		for (lines = 0;
		     (hfreq * 2) / (par->VFT + 1 + 4 * lines) >
		     fb_info.monspecs.vfmax;
		     lines += 2)
			;
		upper_margin += lines;
		lower_margin += lines;
		goto again;
	} else if (vfreq > fb_info.monspecs.vfmax && interlace) {
		/* Interlace, too high -> enlarge margins */
		int lines;
		for (lines = 0;
		     (hfreq * 2) / (par->VFT + 1 + 4 * lines) >
		     fb_info.monspecs.vfmax;
		     lines++)
			;
		upper_margin += lines;
		lower_margin += lines;
		goto again;
	} else if (vfreq < fb_info.monspecs.vfmin ||
		   vfreq > fb_info.monspecs.vfmax)
		return -EINVAL;

set_screen_base:
	linelen = xres_virtual * bpp / 8;
	if (yres_virtual * linelen > screen_len && screen_len)
		return -EINVAL;
	if (yres * linelen > screen_len && screen_len)
		return -EINVAL;
	if (var->yoffset + yres > yres_virtual && yres_virtual)
		return -EINVAL;
	par->yres_virtual = yres_virtual;
	par->screen_base = screen_base + var->yoffset * linelen;
	par->hw.falcon.xoffset = 0;

	par->next_line = linelen;

	return 0;
}