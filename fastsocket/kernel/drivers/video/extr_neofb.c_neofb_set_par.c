#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int vsync_start ;
struct neofb_par {int* Attribute; int* CRTC; int ExtCRTOffset; int ExtColorModeSelect; int ExtCRTDispAddr; int VerticalExt; int SysIfaceCntl1; int SysIfaceCntl2; int PanelDispCntlRegRead; int PanelDispCntlReg1; int GeneralLockReg; int ProgramVCLK; int PanelDispCntlReg2; int PanelDispCntlReg3; scalar_t__ NeoPanelWidth; int PanelVertCenterReg1; int PanelVertCenterReg2; int PanelVertCenterReg3; int PanelVertCenterReg4; int PanelVertCenterReg5; int PanelHorizCenterReg1; int PanelHorizCenterReg2; int PanelHorizCenterReg3; int PanelHorizCenterReg4; int PanelHorizCenterReg5; int NeoPanelHeight; int biosMode; int MiscOutReg; int VCLK3NumeratorLow; int VCLK3Denominator; int VCLK3NumeratorHigh; int /*<<< orphan*/  state; scalar_t__ lcd_stretch; scalar_t__ external_display; scalar_t__ internal_display; scalar_t__ pci_burst; } ;
struct TYPE_5__ {int yres; int lower_margin; int vsync_len; int upper_margin; int bits_per_pixel; int xres_virtual; scalar_t__ xres; int /*<<< orphan*/  pixclock; } ;
struct TYPE_4__ {int accel; int line_length; void* visual; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ fix; struct neofb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int EINVAL ; 
#define  FB_ACCEL_NEOMAGIC_NM2070 136 
#define  FB_ACCEL_NEOMAGIC_NM2090 135 
#define  FB_ACCEL_NEOMAGIC_NM2093 134 
#define  FB_ACCEL_NEOMAGIC_NM2097 133 
#define  FB_ACCEL_NEOMAGIC_NM2160 132 
#define  FB_ACCEL_NEOMAGIC_NM2200 131 
#define  FB_ACCEL_NEOMAGIC_NM2230 130 
#define  FB_ACCEL_NEOMAGIC_NM2360 129 
#define  FB_ACCEL_NEOMAGIC_NM2380 128 
 void* FB_VISUAL_PSEUDOCOLOR ; 
 void* FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  PICOS2KHZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  neo2200_accel_init (struct fb_info*,TYPE_2__*) ; 
 int /*<<< orphan*/  neoCalcVCLK (struct fb_info*,struct neofb_par*,int /*<<< orphan*/ ) ; 
 int neoFindMode (int,int,int) ; 
 int /*<<< orphan*/  neoLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neoUnlock () ; 
 int /*<<< orphan*/  outb (int,int) ; 
 scalar_t__ vgaHWInit (TYPE_2__*,struct neofb_par*) ; 
 int /*<<< orphan*/  vgaHWProtect (int) ; 
 int /*<<< orphan*/  vgaHWRestore (struct fb_info*,struct neofb_par*) ; 
 int vga_rgfx (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vga_wcrt (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vga_wgfx (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int neofb_set_par(struct fb_info *info)
{
	struct neofb_par *par = info->par;
	unsigned char temp;
	int i, clock_hi = 0;
	int lcd_stretch;
	int hoffset, voffset;
	int vsync_start, vtotal;

	DBG("neofb_set_par");

	neoUnlock();

	vgaHWProtect(1);	/* Blank the screen */

	vsync_start = info->var.yres + info->var.lower_margin;
	vtotal = vsync_start + info->var.vsync_len + info->var.upper_margin;

	/*
	 * This will allocate the datastructure and initialize all of the
	 * generic VGA registers.
	 */

	if (vgaHWInit(&info->var, par))
		return -EINVAL;

	/*
	 * The default value assigned by vgaHW.c is 0x41, but this does
	 * not work for NeoMagic.
	 */
	par->Attribute[16] = 0x01;

	switch (info->var.bits_per_pixel) {
	case 8:
		par->CRTC[0x13] = info->var.xres_virtual >> 3;
		par->ExtCRTOffset = info->var.xres_virtual >> 11;
		par->ExtColorModeSelect = 0x11;
		break;
	case 16:
		par->CRTC[0x13] = info->var.xres_virtual >> 2;
		par->ExtCRTOffset = info->var.xres_virtual >> 10;
		par->ExtColorModeSelect = 0x13;
		break;
	case 24:
		par->CRTC[0x13] = (info->var.xres_virtual * 3) >> 3;
		par->ExtCRTOffset = (info->var.xres_virtual * 3) >> 11;
		par->ExtColorModeSelect = 0x14;
		break;
#ifdef NO_32BIT_SUPPORT_YET
	case 32:		/* FIXME: guessed values */
		par->CRTC[0x13] = info->var.xres_virtual >> 1;
		par->ExtCRTOffset = info->var.xres_virtual >> 9;
		par->ExtColorModeSelect = 0x15;
		break;
#endif
	default:
		break;
	}

	par->ExtCRTDispAddr = 0x10;

	/* Vertical Extension */
	par->VerticalExt = (((vtotal - 2) & 0x400) >> 10)
	    | (((info->var.yres - 1) & 0x400) >> 9)
	    | (((vsync_start) & 0x400) >> 8)
	    | (((vsync_start) & 0x400) >> 7);

	/* Fast write bursts on unless disabled. */
	if (par->pci_burst)
		par->SysIfaceCntl1 = 0x30;
	else
		par->SysIfaceCntl1 = 0x00;

	par->SysIfaceCntl2 = 0xc0;	/* VESA Bios sets this to 0x80! */

	/* Initialize: by default, we want display config register to be read */
	par->PanelDispCntlRegRead = 1;

	/* Enable any user specified display devices. */
	par->PanelDispCntlReg1 = 0x00;
	if (par->internal_display)
		par->PanelDispCntlReg1 |= 0x02;
	if (par->external_display)
		par->PanelDispCntlReg1 |= 0x01;

	/* If the user did not specify any display devices, then... */
	if (par->PanelDispCntlReg1 == 0x00) {
		/* Default to internal (i.e., LCD) only. */
		par->PanelDispCntlReg1 = vga_rgfx(NULL, 0x20) & 0x03;
	}

	/* If we are using a fixed mode, then tell the chip we are. */
	switch (info->var.xres) {
	case 1280:
		par->PanelDispCntlReg1 |= 0x60;
		break;
	case 1024:
		par->PanelDispCntlReg1 |= 0x40;
		break;
	case 800:
		par->PanelDispCntlReg1 |= 0x20;
		break;
	case 640:
	default:
		break;
	}

	/* Setup shadow register locking. */
	switch (par->PanelDispCntlReg1 & 0x03) {
	case 0x01:		/* External CRT only mode: */
		par->GeneralLockReg = 0x00;
		/* We need to program the VCLK for external display only mode. */
		par->ProgramVCLK = 1;
		break;
	case 0x02:		/* Internal LCD only mode: */
	case 0x03:		/* Simultaneous internal/external (LCD/CRT) mode: */
		par->GeneralLockReg = 0x01;
		/* Don't program the VCLK when using the LCD. */
		par->ProgramVCLK = 0;
		break;
	}

	/*
	 * If the screen is to be stretched, turn on stretching for the
	 * various modes.
	 *
	 * OPTION_LCD_STRETCH means stretching should be turned off!
	 */
	par->PanelDispCntlReg2 = 0x00;
	par->PanelDispCntlReg3 = 0x00;

	if (par->lcd_stretch && (par->PanelDispCntlReg1 == 0x02) &&	/* LCD only */
	    (info->var.xres != par->NeoPanelWidth)) {
		switch (info->var.xres) {
		case 320:	/* Needs testing.  KEM -- 24 May 98 */
		case 400:	/* Needs testing.  KEM -- 24 May 98 */
		case 640:
		case 800:
		case 1024:
			lcd_stretch = 1;
			par->PanelDispCntlReg2 |= 0xC6;
			break;
		default:
			lcd_stretch = 0;
			/* No stretching in these modes. */
		}
	} else
		lcd_stretch = 0;

	/*
	 * If the screen is to be centerd, turn on the centering for the
	 * various modes.
	 */
	par->PanelVertCenterReg1 = 0x00;
	par->PanelVertCenterReg2 = 0x00;
	par->PanelVertCenterReg3 = 0x00;
	par->PanelVertCenterReg4 = 0x00;
	par->PanelVertCenterReg5 = 0x00;
	par->PanelHorizCenterReg1 = 0x00;
	par->PanelHorizCenterReg2 = 0x00;
	par->PanelHorizCenterReg3 = 0x00;
	par->PanelHorizCenterReg4 = 0x00;
	par->PanelHorizCenterReg5 = 0x00;


	if (par->PanelDispCntlReg1 & 0x02) {
		if (info->var.xres == par->NeoPanelWidth) {
			/*
			 * No centering required when the requested display width
			 * equals the panel width.
			 */
		} else {
			par->PanelDispCntlReg2 |= 0x01;
			par->PanelDispCntlReg3 |= 0x10;

			/* Calculate the horizontal and vertical offsets. */
			if (!lcd_stretch) {
				hoffset =
				    ((par->NeoPanelWidth -
				      info->var.xres) >> 4) - 1;
				voffset =
				    ((par->NeoPanelHeight -
				      info->var.yres) >> 1) - 2;
			} else {
				/* Stretched modes cannot be centered. */
				hoffset = 0;
				voffset = 0;
			}

			switch (info->var.xres) {
			case 320:	/* Needs testing.  KEM -- 24 May 98 */
				par->PanelHorizCenterReg3 = hoffset;
				par->PanelVertCenterReg2 = voffset;
				break;
			case 400:	/* Needs testing.  KEM -- 24 May 98 */
				par->PanelHorizCenterReg4 = hoffset;
				par->PanelVertCenterReg1 = voffset;
				break;
			case 640:
				par->PanelHorizCenterReg1 = hoffset;
				par->PanelVertCenterReg3 = voffset;
				break;
			case 800:
				par->PanelHorizCenterReg2 = hoffset;
				par->PanelVertCenterReg4 = voffset;
				break;
			case 1024:
				par->PanelHorizCenterReg5 = hoffset;
				par->PanelVertCenterReg5 = voffset;
				break;
			case 1280:
			default:
				/* No centering in these modes. */
				break;
			}
		}
	}

	par->biosMode =
	    neoFindMode(info->var.xres, info->var.yres,
			info->var.bits_per_pixel);

	/*
	 * Calculate the VCLK that most closely matches the requested dot
	 * clock.
	 */
	neoCalcVCLK(info, par, PICOS2KHZ(info->var.pixclock));

	/* Since we program the clocks ourselves, always use VCLK3. */
	par->MiscOutReg |= 0x0C;

	/* alread unlocked above */
	/* BOGUS  vga_wgfx(NULL, 0x09, 0x26); */

	/* don't know what this is, but it's 0 from bootup anyway */
	vga_wgfx(NULL, 0x15, 0x00);

	/* was set to 0x01 by my bios in text and vesa modes */
	vga_wgfx(NULL, 0x0A, par->GeneralLockReg);

	/*
	 * The color mode needs to be set before calling vgaHWRestore
	 * to ensure the DAC is initialized properly.
	 *
	 * NOTE: Make sure we don't change bits make sure we don't change
	 * any reserved bits.
	 */
	temp = vga_rgfx(NULL, 0x90);
	switch (info->fix.accel) {
	case FB_ACCEL_NEOMAGIC_NM2070:
		temp &= 0xF0;	/* Save bits 7:4 */
		temp |= (par->ExtColorModeSelect & ~0xF0);
		break;
	case FB_ACCEL_NEOMAGIC_NM2090:
	case FB_ACCEL_NEOMAGIC_NM2093:
	case FB_ACCEL_NEOMAGIC_NM2097:
	case FB_ACCEL_NEOMAGIC_NM2160:
	case FB_ACCEL_NEOMAGIC_NM2200:
	case FB_ACCEL_NEOMAGIC_NM2230:
	case FB_ACCEL_NEOMAGIC_NM2360:
	case FB_ACCEL_NEOMAGIC_NM2380:
		temp &= 0x70;	/* Save bits 6:4 */
		temp |= (par->ExtColorModeSelect & ~0x70);
		break;
	}

	vga_wgfx(NULL, 0x90, temp);

	/*
	 * In some rare cases a lockup might occur if we don't delay
	 * here. (Reported by Miles Lane)
	 */
	//mdelay(200);

	/*
	 * Disable horizontal and vertical graphics and text expansions so
	 * that vgaHWRestore works properly.
	 */
	temp = vga_rgfx(NULL, 0x25);
	temp &= 0x39;
	vga_wgfx(NULL, 0x25, temp);

	/*
	 * Sleep for 200ms to make sure that the two operations above have
	 * had time to take effect.
	 */
	mdelay(200);

	/*
	 * This function handles restoring the generic VGA registers.  */
	vgaHWRestore(info, par);

	/* linear colormap for non palettized modes */
	switch (info->var.bits_per_pixel) {
	case 8:
		/* PseudoColor, 256 */
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		break;
	case 16:
		/* TrueColor, 64k */
		info->fix.visual = FB_VISUAL_TRUECOLOR;

		for (i = 0; i < 64; i++) {
			outb(i, 0x3c8);

			outb(i << 1, 0x3c9);
			outb(i, 0x3c9);
			outb(i << 1, 0x3c9);
		}
		break;
	case 24:
#ifdef NO_32BIT_SUPPORT_YET
	case 32:
#endif
		/* TrueColor, 16m */
		info->fix.visual = FB_VISUAL_TRUECOLOR;

		for (i = 0; i < 256; i++) {
			outb(i, 0x3c8);

			outb(i, 0x3c9);
			outb(i, 0x3c9);
			outb(i, 0x3c9);
		}
		break;
	}

	vga_wgfx(NULL, 0x0E, par->ExtCRTDispAddr);
	vga_wgfx(NULL, 0x0F, par->ExtCRTOffset);
	temp = vga_rgfx(NULL, 0x10);
	temp &= 0x0F;		/* Save bits 3:0 */
	temp |= (par->SysIfaceCntl1 & ~0x0F);	/* VESA Bios sets bit 1! */
	vga_wgfx(NULL, 0x10, temp);

	vga_wgfx(NULL, 0x11, par->SysIfaceCntl2);
	vga_wgfx(NULL, 0x15, 0 /*par->SingleAddrPage */ );
	vga_wgfx(NULL, 0x16, 0 /*par->DualAddrPage */ );

	temp = vga_rgfx(NULL, 0x20);
	switch (info->fix.accel) {
	case FB_ACCEL_NEOMAGIC_NM2070:
		temp &= 0xFC;	/* Save bits 7:2 */
		temp |= (par->PanelDispCntlReg1 & ~0xFC);
		break;
	case FB_ACCEL_NEOMAGIC_NM2090:
	case FB_ACCEL_NEOMAGIC_NM2093:
	case FB_ACCEL_NEOMAGIC_NM2097:
	case FB_ACCEL_NEOMAGIC_NM2160:
		temp &= 0xDC;	/* Save bits 7:6,4:2 */
		temp |= (par->PanelDispCntlReg1 & ~0xDC);
		break;
	case FB_ACCEL_NEOMAGIC_NM2200:
	case FB_ACCEL_NEOMAGIC_NM2230:
	case FB_ACCEL_NEOMAGIC_NM2360:
	case FB_ACCEL_NEOMAGIC_NM2380:
		temp &= 0x98;	/* Save bits 7,4:3 */
		temp |= (par->PanelDispCntlReg1 & ~0x98);
		break;
	}
	vga_wgfx(NULL, 0x20, temp);

	temp = vga_rgfx(NULL, 0x25);
	temp &= 0x38;		/* Save bits 5:3 */
	temp |= (par->PanelDispCntlReg2 & ~0x38);
	vga_wgfx(NULL, 0x25, temp);

	if (info->fix.accel != FB_ACCEL_NEOMAGIC_NM2070) {
		temp = vga_rgfx(NULL, 0x30);
		temp &= 0xEF;	/* Save bits 7:5 and bits 3:0 */
		temp |= (par->PanelDispCntlReg3 & ~0xEF);
		vga_wgfx(NULL, 0x30, temp);
	}

	vga_wgfx(NULL, 0x28, par->PanelVertCenterReg1);
	vga_wgfx(NULL, 0x29, par->PanelVertCenterReg2);
	vga_wgfx(NULL, 0x2a, par->PanelVertCenterReg3);

	if (info->fix.accel != FB_ACCEL_NEOMAGIC_NM2070) {
		vga_wgfx(NULL, 0x32, par->PanelVertCenterReg4);
		vga_wgfx(NULL, 0x33, par->PanelHorizCenterReg1);
		vga_wgfx(NULL, 0x34, par->PanelHorizCenterReg2);
		vga_wgfx(NULL, 0x35, par->PanelHorizCenterReg3);
	}

	if (info->fix.accel == FB_ACCEL_NEOMAGIC_NM2160)
		vga_wgfx(NULL, 0x36, par->PanelHorizCenterReg4);

	if (info->fix.accel == FB_ACCEL_NEOMAGIC_NM2200 ||
	    info->fix.accel == FB_ACCEL_NEOMAGIC_NM2230 ||
	    info->fix.accel == FB_ACCEL_NEOMAGIC_NM2360 ||
	    info->fix.accel == FB_ACCEL_NEOMAGIC_NM2380) {
		vga_wgfx(NULL, 0x36, par->PanelHorizCenterReg4);
		vga_wgfx(NULL, 0x37, par->PanelVertCenterReg5);
		vga_wgfx(NULL, 0x38, par->PanelHorizCenterReg5);

		clock_hi = 1;
	}

	/* Program VCLK3 if needed. */
	if (par->ProgramVCLK && ((vga_rgfx(NULL, 0x9B) != par->VCLK3NumeratorLow)
				 || (vga_rgfx(NULL, 0x9F) != par->VCLK3Denominator)
				 || (clock_hi && ((vga_rgfx(NULL, 0x8F) & ~0x0f)
						  != (par->VCLK3NumeratorHigh &
						      ~0x0F))))) {
		vga_wgfx(NULL, 0x9B, par->VCLK3NumeratorLow);
		if (clock_hi) {
			temp = vga_rgfx(NULL, 0x8F);
			temp &= 0x0F;	/* Save bits 3:0 */
			temp |= (par->VCLK3NumeratorHigh & ~0x0F);
			vga_wgfx(NULL, 0x8F, temp);
		}
		vga_wgfx(NULL, 0x9F, par->VCLK3Denominator);
	}

	if (par->biosMode)
		vga_wcrt(NULL, 0x23, par->biosMode);

	vga_wgfx(NULL, 0x93, 0xc0);	/* Gives 5x faster framebuffer writes !!! */

	/* Program vertical extension register */
	if (info->fix.accel == FB_ACCEL_NEOMAGIC_NM2200 ||
	    info->fix.accel == FB_ACCEL_NEOMAGIC_NM2230 ||
	    info->fix.accel == FB_ACCEL_NEOMAGIC_NM2360 ||
	    info->fix.accel == FB_ACCEL_NEOMAGIC_NM2380) {
		vga_wcrt(NULL, 0x70, par->VerticalExt);
	}

	vgaHWProtect(0);	/* Turn on screen */

	/* Calling this also locks offset registers required in update_start */
	neoLock(&par->state);

	info->fix.line_length =
	    info->var.xres_virtual * (info->var.bits_per_pixel >> 3);

	switch (info->fix.accel) {
		case FB_ACCEL_NEOMAGIC_NM2200:
		case FB_ACCEL_NEOMAGIC_NM2230: 
		case FB_ACCEL_NEOMAGIC_NM2360: 
		case FB_ACCEL_NEOMAGIC_NM2380: 
			neo2200_accel_init(info, &info->var);
			break;
		default:
			break;
	}	
	return 0;
}