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
typedef  int u32 ;
struct gxt4500_par {int pll_n; int pll_m; int pll_pd2; int pll_pd1; unsigned int pixfmt; } ;
struct fb_var_screeninfo {unsigned int xres; unsigned int left_margin; unsigned int right_margin; unsigned int hsync_len; int yres; int upper_margin; int lower_margin; int vsync_len; int pixclock; int xres_virtual; int xoffset; int yoffset; int sync; } ;
struct TYPE_2__ {unsigned int line_length; int /*<<< orphan*/  visual; } ;
struct fb_info {TYPE_1__ fix; struct fb_var_screeninfo var; struct gxt4500_par* par; } ;

/* Variables and functions */
 int CR0_RASTER_RESET ; 
 scalar_t__ CTRL_REG0 ; 
 scalar_t__ CURSOR_MODE ; 
 int CURSOR_MODE_OFF ; 
 scalar_t__ DFA_FB_A ; 
 unsigned int DFA_FB_ENABLE ; 
 unsigned int DFA_FB_STRIDE_1k ; 
 unsigned int DFA_FB_STRIDE_2k ; 
 unsigned int DFA_FB_STRIDE_4k ; 
 unsigned int DFA_PIX_8BIT ; 
 scalar_t__ DTG_CONTROL ; 
 int DTG_CTL_ENABLE ; 
 int DTG_CTL_SCREEN_REFRESH ; 
 scalar_t__ DTG_HORIZ_DISPLAY ; 
 scalar_t__ DTG_HORIZ_EXTENT ; 
 scalar_t__ DTG_HSYNC_END ; 
 scalar_t__ DTG_HSYNC_END_COMP ; 
 scalar_t__ DTG_HSYNC_START ; 
 scalar_t__ DTG_VERT_DISPLAY ; 
 scalar_t__ DTG_VERT_EXTENT ; 
 scalar_t__ DTG_VERT_SHORT ; 
 scalar_t__ DTG_VSYNC_END ; 
 scalar_t__ DTG_VSYNC_START ; 
 scalar_t__ FB_AB_CTRL ; 
 scalar_t__ FB_CD_CTRL ; 
 unsigned int FB_CTRL_TYPE ; 
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_ON_GREEN ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int /*<<< orphan*/  FB_VISUAL_DIRECTCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 scalar_t__ PLL_C ; 
 scalar_t__ PLL_M ; 
 scalar_t__ PLL_N ; 
 scalar_t__ PLL_POSTDIV ; 
 scalar_t__ REFRESH_AB_CTRL ; 
 scalar_t__ REFRESH_CD_CTRL ; 
 scalar_t__ REFRESH_SIZE ; 
 scalar_t__ REFRESH_START ; 
 scalar_t__ SYNC_CTL ; 
 int SYNC_CTL_HSYNC_INV ; 
 int SYNC_CTL_SYNC_ON_RGB ; 
 int SYNC_CTL_VSYNC_INV ; 
 scalar_t__ WAT_CMAP_OFFSET ; 
 scalar_t__ WAT_CTRL ; 
 scalar_t__ WAT_FMT ; 
 scalar_t__ WAT_GAMMA_CTRL ; 
 int WAT_GAMMA_DISABLE ; 
 int gxt4500_var_to_par (struct fb_var_screeninfo*,struct gxt4500_par*) ; 
 int* mdivtab ; 
 int /*<<< orphan*/  msleep (int) ; 
 int* ndivtab ; 
 unsigned int* pixsize ; 
 int readreg (struct gxt4500_par*,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int* watfmt ; 
 int /*<<< orphan*/  writereg (struct gxt4500_par*,scalar_t__,int) ; 

__attribute__((used)) static int gxt4500_set_par(struct fb_info *info)
{
	struct gxt4500_par *par = info->par;
	struct fb_var_screeninfo *var = &info->var;
	int err;
	u32 ctrlreg, tmp;
	unsigned int dfa_ctl, pixfmt, stride;
	unsigned int wid_tiles, i;
	unsigned int prefetch_pix, htot;
	struct gxt4500_par save_par;

	save_par = *par;
	err = gxt4500_var_to_par(var, par);
	if (err) {
		*par = save_par;
		return err;
	}

	/* turn off DTG for now */
	ctrlreg = readreg(par, DTG_CONTROL);
	ctrlreg &= ~(DTG_CTL_ENABLE | DTG_CTL_SCREEN_REFRESH);
	writereg(par, DTG_CONTROL, ctrlreg);

	/* set PLL registers */
	tmp = readreg(par, PLL_C) & ~0x7f;
	if (par->pll_n < 38)
		tmp |= 0x29;
	if (par->pll_n < 69)
		tmp |= 0x35;
	else if (par->pll_n < 100)
		tmp |= 0x76;
	else
		tmp |= 0x7e;
	writereg(par, PLL_C, tmp);
	writereg(par, PLL_M, mdivtab[par->pll_m - 1]);
	writereg(par, PLL_N, ndivtab[par->pll_n - 2]);
	tmp = ((8 - par->pll_pd2) << 3) | (8 - par->pll_pd1);
	if (par->pll_pd1 == 8 || par->pll_pd2 == 8) {
		/* work around erratum */
		writereg(par, PLL_POSTDIV, tmp | 0x9);
		udelay(1);
	}
	writereg(par, PLL_POSTDIV, tmp);
	msleep(20);

	/* turn off hardware cursor */
	writereg(par, CURSOR_MODE, CURSOR_MODE_OFF);

	/* reset raster engine */
	writereg(par, CTRL_REG0, CR0_RASTER_RESET | (CR0_RASTER_RESET << 16));
	udelay(10);
	writereg(par, CTRL_REG0, CR0_RASTER_RESET << 16);

	/* set display timing generator registers */
	htot = var->xres + var->left_margin + var->right_margin +
		var->hsync_len;
	writereg(par, DTG_HORIZ_EXTENT, htot - 1);
	writereg(par, DTG_HORIZ_DISPLAY, var->xres - 1);
	writereg(par, DTG_HSYNC_START, var->xres + var->right_margin - 1);
	writereg(par, DTG_HSYNC_END,
		 var->xres + var->right_margin + var->hsync_len - 1);
	writereg(par, DTG_HSYNC_END_COMP,
		 var->xres + var->right_margin + var->hsync_len - 1);
	writereg(par, DTG_VERT_EXTENT,
		 var->yres + var->upper_margin + var->lower_margin +
		 var->vsync_len - 1);
	writereg(par, DTG_VERT_DISPLAY, var->yres - 1);
	writereg(par, DTG_VSYNC_START, var->yres + var->lower_margin - 1);
	writereg(par, DTG_VSYNC_END,
		 var->yres + var->lower_margin + var->vsync_len - 1);
	prefetch_pix = 3300000 / var->pixclock;
	if (prefetch_pix >= htot)
		prefetch_pix = htot - 1;
	writereg(par, DTG_VERT_SHORT, htot - prefetch_pix - 1);
	ctrlreg |= DTG_CTL_ENABLE | DTG_CTL_SCREEN_REFRESH;
	writereg(par, DTG_CONTROL, ctrlreg);

	/* calculate stride in DFA aperture */
	if (var->xres_virtual > 2048) {
		stride = 4096;
		dfa_ctl = DFA_FB_STRIDE_4k;
	} else if (var->xres_virtual > 1024) {
		stride = 2048;
		dfa_ctl = DFA_FB_STRIDE_2k;
	} else {
		stride = 1024;
		dfa_ctl = DFA_FB_STRIDE_1k;
	}

	/* Set up framebuffer definition */
	wid_tiles = (var->xres_virtual + 63) >> 6;

	/* XXX add proper FB allocation here someday */
	writereg(par, FB_AB_CTRL, FB_CTRL_TYPE | (wid_tiles << 16) | 0);
	writereg(par, REFRESH_AB_CTRL, FB_CTRL_TYPE | (wid_tiles << 16) | 0);
	writereg(par, FB_CD_CTRL, FB_CTRL_TYPE | (wid_tiles << 16) | 0);
	writereg(par, REFRESH_CD_CTRL, FB_CTRL_TYPE | (wid_tiles << 16) | 0);
	writereg(par, REFRESH_START, (var->xoffset << 16) | var->yoffset);
	writereg(par, REFRESH_SIZE, (var->xres << 16) | var->yres);

	/* Set up framebuffer access by CPU */

	pixfmt = par->pixfmt;
	dfa_ctl |= DFA_FB_ENABLE | pixfmt;
	writereg(par, DFA_FB_A, dfa_ctl);

	/*
	 * Set up window attribute table.
	 * We set all WAT entries the same so it doesn't matter what the
	 * window ID (WID) plane contains.
	 */
	for (i = 0; i < 32; ++i) {
		writereg(par, WAT_FMT + (i << 4), watfmt[pixfmt]);
		writereg(par, WAT_CMAP_OFFSET + (i << 4), 0);
		writereg(par, WAT_CTRL + (i << 4), 0);
		writereg(par, WAT_GAMMA_CTRL + (i << 4), WAT_GAMMA_DISABLE);
	}

	/* Set sync polarity etc. */
	ctrlreg = readreg(par, SYNC_CTL) &
		~(SYNC_CTL_SYNC_ON_RGB | SYNC_CTL_HSYNC_INV |
		  SYNC_CTL_VSYNC_INV);
	if (var->sync & FB_SYNC_ON_GREEN)
		ctrlreg |= SYNC_CTL_SYNC_ON_RGB;
	if (!(var->sync & FB_SYNC_HOR_HIGH_ACT))
		ctrlreg |= SYNC_CTL_HSYNC_INV;
	if (!(var->sync & FB_SYNC_VERT_HIGH_ACT))
		ctrlreg |= SYNC_CTL_VSYNC_INV;
	writereg(par, SYNC_CTL, ctrlreg);

	info->fix.line_length = stride * pixsize[pixfmt];
	info->fix.visual = (pixfmt == DFA_PIX_8BIT)? FB_VISUAL_PSEUDOCOLOR:
		FB_VISUAL_DIRECTCOLOR;

	return 0;
}