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
typedef  int ushort ;
typedef  int u32 ;
struct pixclock_div {int /*<<< orphan*/  p; int /*<<< orphan*/  n; int /*<<< orphan*/  m; } ;
struct TYPE_4__ {int length; } ;
struct fb_var_screeninfo {int xres_virtual; int bits_per_pixel; int xres; int yres; int hsync_len; int left_margin; int right_margin; int vsync_len; int upper_margin; int lower_margin; int /*<<< orphan*/  pixclock; TYPE_2__ green; } ;
struct TYPE_3__ {int line_length; int /*<<< orphan*/  visual; } ;
struct fb_info {struct fb_var_screeninfo var; TYPE_1__ fix; int /*<<< orphan*/  cmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DHDET ; 
 int /*<<< orphan*/  DHT01 ; 
 int /*<<< orphan*/  DHT02 ; 
 int /*<<< orphan*/  DHT03 ; 
 int /*<<< orphan*/  DINTRE ; 
 int DINTRE_VEVENT0_EN ; 
 int /*<<< orphan*/  DISPPLL ; 
 int DISP_PLL_EN ; 
 int /*<<< orphan*/  DSCTRL ; 
 int DSCTRL_SYNCGEN_EN ; 
 int /*<<< orphan*/  DVDET ; 
 int /*<<< orphan*/  DVECTRL ; 
 int /*<<< orphan*/  DVT01 ; 
 int /*<<< orphan*/  DVT02 ; 
 int /*<<< orphan*/  DVT03 ; 
 int Dhdet_Hdef (int) ; 
 int Dhdet_Hdes (int) ; 
 int Dht01_Hbps (int) ; 
 int Dht01_Ht (int) ; 
 int Dht02_Has (int) ; 
 int Dht02_Hlbs (int) ; 
 int Dht03_Hfps (int) ; 
 int Dht03_Hrbs (int) ; 
 int Disp_Pll_M (int /*<<< orphan*/ ) ; 
 int Disp_Pll_N (int /*<<< orphan*/ ) ; 
 int Disp_Pll_P (int /*<<< orphan*/ ) ; 
 int Dvdet_Vdef (int) ; 
 int Dvdet_Vdes (int) ; 
 int Dvectrl_Vevent (int) ; 
 int Dvectrl_Vfetch (int) ; 
 int Dvt01_Vbps (int) ; 
 int Dvt01_Vt (int) ; 
 int Dvt02_Vas (int) ; 
 int Dvt02_Vtbs (int) ; 
 int Dvt03_Vbbs (int) ; 
 int Dvt03_Vfps (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int FMsk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSADR ; 
 int /*<<< orphan*/  GSADR_SRCSTRIDE ; 
 int /*<<< orphan*/  GSCTRL ; 
 int /*<<< orphan*/  GSCTRL_GPIXFMT ; 
 int GSCTRL_GPIXFMT_ARGB1555 ; 
 int GSCTRL_GPIXFMT_ARGB8888 ; 
 int GSCTRL_GPIXFMT_RGB565 ; 
 int GSCTRL_GPIXFMT_RGB888 ; 
 int /*<<< orphan*/  GSCTRL_GSHEIGHT ; 
 int /*<<< orphan*/  GSCTRL_GSWIDTH ; 
 int GSCTRL_LUT_EN ; 
 int Gsadr_Srcstride (int) ; 
 int Gsctrl_Height (int) ; 
 int Gsctrl_Width (int) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbxfb_get_pixclock (int /*<<< orphan*/ ,struct pixclock_div*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg_dly (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mbxfb_set_par(struct fb_info *info)
{
	struct fb_var_screeninfo *var = &info->var;
	struct pixclock_div div;
	ushort hbps, ht, hfps, has;
	ushort vbps, vt, vfps, vas;
	u32 gsctrl = readl(GSCTRL);
	u32 gsadr = readl(GSADR);

	info->fix.line_length = var->xres_virtual * var->bits_per_pixel / 8;

	/* setup color mode */
	gsctrl &= ~(FMsk(GSCTRL_GPIXFMT));
	/* FIXME: add *WORKING* support for 8-bits per color */
	if (info->var.bits_per_pixel == 8) {
		return -EINVAL;
	} else {
		fb_dealloc_cmap(&info->cmap);
		gsctrl &= ~GSCTRL_LUT_EN;

		info->fix.visual = FB_VISUAL_TRUECOLOR;
		switch (info->var.bits_per_pixel) {
		case 16:
			if (info->var.green.length == 5)
				gsctrl |= GSCTRL_GPIXFMT_ARGB1555;
			else
				gsctrl |= GSCTRL_GPIXFMT_RGB565;
			break;
		case 24:
			gsctrl |= GSCTRL_GPIXFMT_RGB888;
			break;
		case 32:
			gsctrl |= GSCTRL_GPIXFMT_ARGB8888;
			break;
		}
	}

	/* setup resolution */
	gsctrl &= ~(FMsk(GSCTRL_GSWIDTH) | FMsk(GSCTRL_GSHEIGHT));
	gsctrl |= Gsctrl_Width(info->var.xres) |
		Gsctrl_Height(info->var.yres);
	write_reg_dly(gsctrl, GSCTRL);

	gsadr &= ~(FMsk(GSADR_SRCSTRIDE));
	gsadr |= Gsadr_Srcstride(info->var.xres * info->var.bits_per_pixel /
				 (8 * 16) - 1);
	write_reg_dly(gsadr, GSADR);

	/* setup timings */
	var->pixclock = mbxfb_get_pixclock(info->var.pixclock, &div);

	write_reg_dly((Disp_Pll_M(div.m) | Disp_Pll_N(div.n) |
		Disp_Pll_P(div.p) | DISP_PLL_EN), DISPPLL);

	hbps = var->hsync_len;
	has = hbps + var->left_margin;
	hfps = has + var->xres;
	ht = hfps + var->right_margin;

	vbps = var->vsync_len;
	vas = vbps + var->upper_margin;
	vfps = vas + var->yres;
	vt = vfps + var->lower_margin;

	write_reg_dly((Dht01_Hbps(hbps) | Dht01_Ht(ht)), DHT01);
	write_reg_dly((Dht02_Hlbs(has) | Dht02_Has(has)), DHT02);
	write_reg_dly((Dht03_Hfps(hfps) | Dht03_Hrbs(hfps)), DHT03);
	write_reg_dly((Dhdet_Hdes(has) | Dhdet_Hdef(hfps)), DHDET);

	write_reg_dly((Dvt01_Vbps(vbps) | Dvt01_Vt(vt)), DVT01);
	write_reg_dly((Dvt02_Vtbs(vas) | Dvt02_Vas(vas)), DVT02);
	write_reg_dly((Dvt03_Vfps(vfps) | Dvt03_Vbbs(vfps)), DVT03);
	write_reg_dly((Dvdet_Vdes(vas) | Dvdet_Vdef(vfps)), DVDET);
	write_reg_dly((Dvectrl_Vevent(vfps) | Dvectrl_Vfetch(vbps)), DVECTRL);

	write_reg_dly((readl(DSCTRL) | DSCTRL_SYNCGEN_EN), DSCTRL);

	write_reg_dly(DINTRE_VEVENT0_EN, DINTRE);

	return 0;
}