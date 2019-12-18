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
struct sh7760fb_par {TYPE_2__* pd; scalar_t__ base; scalar_t__ rot; scalar_t__ fbdma; } ;
struct fb_videomode {int xres; unsigned short right_margin; unsigned short hsync_len; unsigned short left_margin; unsigned short lower_margin; unsigned short yres; unsigned short vsync_len; unsigned short upper_margin; int sync; } ;
struct TYPE_3__ {unsigned long line_length; } ;
struct fb_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  var; TYPE_1__ fix; struct sh7760fb_par* par; } ;
struct TYPE_4__ {int lddfr; unsigned short ldmtr; unsigned long ldickr; unsigned long ldpmmr; unsigned long ldpspr; unsigned long ldaclnr; scalar_t__ rotate; struct fb_videomode* def_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 scalar_t__ LDACLNR ; 
 scalar_t__ LDDFR ; 
 scalar_t__ LDHCNR ; 
 scalar_t__ LDHSYNR ; 
 scalar_t__ LDICKR ; 
 scalar_t__ LDLAOR ; 
 scalar_t__ LDMTR ; 
 unsigned short LDMTR_CL1POL ; 
 unsigned short LDMTR_DSTN_COLOR_16 ; 
 unsigned short LDMTR_DSTN_MONO_8 ; 
 unsigned short LDMTR_FLMPOL ; 
 scalar_t__ LDPMMR ; 
 scalar_t__ LDPSPR ; 
 scalar_t__ LDSARL ; 
 scalar_t__ LDSARU ; 
 scalar_t__ LDSMR ; 
 scalar_t__ LDVDLNR ; 
 scalar_t__ LDVSYNR ; 
 scalar_t__ LDVTLNR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  iowrite16 (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  sh7760fb_blank (int /*<<< orphan*/ ,struct fb_info*) ; 
 int /*<<< orphan*/  sh7760fb_check_var (int /*<<< orphan*/ *,struct fb_info*) ; 
 int sh7760fb_get_color_info (int /*<<< orphan*/ ,int,int*,int*) ; 

__attribute__((used)) static int sh7760fb_set_par(struct fb_info *info)
{
	struct sh7760fb_par *par = info->par;
	struct fb_videomode *vm = par->pd->def_mode;
	unsigned long sbase, dstn_off, ldsarl, stride;
	unsigned short hsynp, hsynw, htcn, hdcn;
	unsigned short vsynp, vsynw, vtln, vdln;
	unsigned short lddfr, ldmtr;
	int ret, bpp, gray;

	par->rot = par->pd->rotate;

	/* rotate only works with xres <= 320 */
	if (par->rot && (vm->xres > 320)) {
		dev_dbg(info->dev, "rotation disabled due to display size\n");
		par->rot = 0;
	}

	/* calculate LCDC reg vals from display parameters */
	hsynp = vm->right_margin + vm->xres;
	hsynw = vm->hsync_len;
	htcn = vm->left_margin + hsynp + hsynw;
	hdcn = vm->xres;
	vsynp = vm->lower_margin + vm->yres;
	vsynw = vm->vsync_len;
	vtln = vm->upper_margin + vsynp + vsynw;
	vdln = vm->yres;

	/* get color info from register value */
	ret = sh7760fb_get_color_info(info->dev, par->pd->lddfr, &bpp, &gray);
	if (ret)
		return ret;

	dev_dbg(info->dev, "%dx%d %dbpp %s (orientation %s)\n", hdcn,
		vdln, bpp, gray ? "grayscale" : "color",
		par->rot ? "rotated" : "normal");

#ifdef CONFIG_CPU_LITTLE_ENDIAN
	lddfr = par->pd->lddfr | (1 << 8);
#else
	lddfr = par->pd->lddfr & ~(1 << 8);
#endif

	ldmtr = par->pd->ldmtr;

	if (!(vm->sync & FB_SYNC_HOR_HIGH_ACT))
		ldmtr |= LDMTR_CL1POL;
	if (!(vm->sync & FB_SYNC_VERT_HIGH_ACT))
		ldmtr |= LDMTR_FLMPOL;

	/* shut down LCDC before changing display parameters */
	sh7760fb_blank(FB_BLANK_POWERDOWN, info);

	iowrite16(par->pd->ldickr, par->base + LDICKR);	/* pixclock */
	iowrite16(ldmtr, par->base + LDMTR);	/* polarities */
	iowrite16(lddfr, par->base + LDDFR);	/* color/depth */
	iowrite16((par->rot ? 1 << 13 : 0), par->base + LDSMR);	/* rotate */
	iowrite16(par->pd->ldpmmr, par->base + LDPMMR);	/* Power Management */
	iowrite16(par->pd->ldpspr, par->base + LDPSPR);	/* Power Supply Ctrl */

	/* display resolution */
	iowrite16(((htcn >> 3) - 1) | (((hdcn >> 3) - 1) << 8),
		  par->base + LDHCNR);
	iowrite16(vdln - 1, par->base + LDVDLNR);
	iowrite16(vtln - 1, par->base + LDVTLNR);
	/* h/v sync signals */
	iowrite16((vsynp - 1) | ((vsynw - 1) << 12), par->base + LDVSYNR);
	iowrite16(((hsynp >> 3) - 1) | (((hsynw >> 3) - 1) << 12),
		  par->base + LDHSYNR);
	/* AC modulation sig */
	iowrite16(par->pd->ldaclnr, par->base + LDACLNR);

	stride = (par->rot) ? vtln : hdcn;
	if (!gray)
		stride *= (bpp + 7) >> 3;
	else {
		if (bpp == 1)
			stride >>= 3;
		else if (bpp == 2)
			stride >>= 2;
		else if (bpp == 4)
			stride >>= 1;
		/* 6 bpp == 8 bpp */
	}

	/* if rotated, stride must be power of 2 */
	if (par->rot) {
		unsigned long bit = 1 << 31;
		while (bit) {
			if (stride & bit)
				break;
			bit >>= 1;
		}
		if (stride & ~bit)
			stride = bit << 1;	/* not P-o-2, round up */
	}
	iowrite16(stride, par->base + LDLAOR);

	/* set display mem start address */
	sbase = (unsigned long)par->fbdma;
	if (par->rot)
		sbase += (hdcn - 1) * stride;

	iowrite32(sbase, par->base + LDSARU);

	/*
	 * for DSTN need to set address for lower half.
	 * I (mlau) don't know which address to set it to,
	 * so I guessed at (stride * yres/2).
	 */
	if (((ldmtr & 0x003f) >= LDMTR_DSTN_MONO_8) &&
	    ((ldmtr & 0x003f) <= LDMTR_DSTN_COLOR_16)) {

		dev_dbg(info->dev, " ***** DSTN untested! *****\n");

		dstn_off = stride;
		if (par->rot)
			dstn_off *= hdcn >> 1;
		else
			dstn_off *= vdln >> 1;

		ldsarl = sbase + dstn_off;
	} else
		ldsarl = 0;

	iowrite32(ldsarl, par->base + LDSARL);	/* mem for lower half of DSTN */

	info->fix.line_length = stride;

	sh7760fb_check_var(&info->var, info);

	sh7760fb_blank(FB_BLANK_UNBLANK, info);	/* panel on! */

	dev_dbg(info->dev, "hdcn  : %6d htcn  : %6d\n", hdcn, htcn);
	dev_dbg(info->dev, "hsynw : %6d hsynp : %6d\n", hsynw, hsynp);
	dev_dbg(info->dev, "vdln  : %6d vtln  : %6d\n", vdln, vtln);
	dev_dbg(info->dev, "vsynw : %6d vsynp : %6d\n", vsynw, vsynp);
	dev_dbg(info->dev, "clksrc: %6d clkdiv: %6d\n",
		(par->pd->ldickr >> 12) & 3, par->pd->ldickr & 0x1f);
	dev_dbg(info->dev, "ldpmmr: 0x%04x ldpspr: 0x%04x\n", par->pd->ldpmmr,
		par->pd->ldpspr);
	dev_dbg(info->dev, "ldmtr : 0x%04x lddfr : 0x%04x\n", ldmtr, lddfr);
	dev_dbg(info->dev, "ldlaor: %ld\n", stride);
	dev_dbg(info->dev, "ldsaru: 0x%08lx ldsarl: 0x%08lx\n", sbase, ldsarl);

	return 0;
}