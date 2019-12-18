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
struct TYPE_4__ {int /*<<< orphan*/  (* set_pll ) (struct fb_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_vidmod ) (struct fb_info*,int /*<<< orphan*/ ) ;} ;
struct sstfb_par {int hSyncOff; int yDim; int vSyncOn; int vSyncOff; int vBackPorch; int tiles_in_X; int /*<<< orphan*/  pll; TYPE_2__ dac_sw; struct pci_dev* dev; } ;
struct pci_dev {int dummy; } ;
struct TYPE_3__ {int xres; int right_margin; int left_margin; int yres; int vsync_len; int lower_margin; int upper_margin; int vmode; int hsync_len; int sync; int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  pixclock; } ;
struct fb_info {TYPE_1__ var; struct sstfb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKPORCH ; 
 int /*<<< orphan*/  CLIP_LEFT_RIGHT ; 
 int /*<<< orphan*/  CLIP_LOWY_HIGHY ; 
 int EINVAL ; 
 int EN_BLANK_OE ; 
 int EN_CLIPPING ; 
 int EN_DATA_OE ; 
 int EN_DCLK_OE ; 
 int EN_DRAM_REFRESH ; 
 int EN_HVSYNC_OE ; 
 int EN_PXL_PIPELINE ; 
 int EN_RGB_WRITE ; 
 int /*<<< orphan*/  FBIINIT0 ; 
 int /*<<< orphan*/  FBIINIT1 ; 
 int /*<<< orphan*/  FBIINIT2 ; 
 int /*<<< orphan*/  FBIINIT3 ; 
 int /*<<< orphan*/  FBIINIT5 ; 
 int FBIINIT5_MASK ; 
 int /*<<< orphan*/  FBIINIT6 ; 
 int FBI_RESET ; 
 int /*<<< orphan*/  FBZMODE ; 
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int FB_VMODE_DOUBLE ; 
 int FB_VMODE_INTERLACED ; 
 int FIFO_RESET ; 
 int /*<<< orphan*/  HSYNC ; 
 int HSYNC_HIGH ; 
 int INTERLACE ; 
 scalar_t__ IS_VOODOO2 (struct sstfb_par*) ; 
 int /*<<< orphan*/  LFBMODE ; 
 int LFB_565 ; 
 int LFB_BYTE_SWIZZLE_RD ; 
 int LFB_BYTE_SWIZZLE_WR ; 
 int LFB_WORD_SWIZZLE_RD ; 
 int LFB_WORD_SWIZZLE_WR ; 
 int /*<<< orphan*/  NOPCMD ; 
 int PCI_EN_FIFO_WR ; 
 int PCI_EN_INIT_WR ; 
 int /*<<< orphan*/  PCI_INIT_ENABLE ; 
 int PCI_REMAP_DAC ; 
 int /*<<< orphan*/  PICOS2KHZ (int /*<<< orphan*/ ) ; 
 int SEL_INPUT_VCLK_2X ; 
 int SEL_SOURCE_VCLK_2X_SEL ; 
 int TILES_IN_X_LSB_SHIFT ; 
 int TILES_IN_X_MSB_SHIFT ; 
 int TILES_IN_X_SHIFT ; 
 int VDOUBLESCAN ; 
 int /*<<< orphan*/  VIDEODIMENSIONS ; 
 int VIDEO_MASK ; 
 int VIDEO_RESET ; 
 int /*<<< orphan*/  VID_CLOCK ; 
 int /*<<< orphan*/  VSYNC ; 
 int VSYNC_HIGH ; 
 scalar_t__ clipping ; 
 int /*<<< orphan*/  f_ddprintk (char*,...) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sst_calc_pll (int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ *) ; 
 int sst_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_set_bits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sst_unset_bits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sst_wait_idle () ; 
 int /*<<< orphan*/  sst_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct fb_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sstfb_set_par(struct fb_info *info)
{
	struct sstfb_par *par = info->par;
	u32 lfbmode, fbiinit1, fbiinit2, fbiinit3, fbiinit5, fbiinit6=0;
	struct pci_dev *sst_dev = par->dev;
	unsigned int freq;
	int ntiles;

	par->hSyncOff	= info->var.xres + info->var.right_margin + info->var.left_margin;

	par->yDim 	= info->var.yres;
	par->vSyncOn 	= info->var.vsync_len;
	par->vSyncOff	= info->var.yres + info->var.lower_margin + info->var.upper_margin;
	par->vBackPorch = info->var.upper_margin;

	/* We need par->pll */
	sst_calc_pll(PICOS2KHZ(info->var.pixclock), &freq, &par->pll);

	if (info->var.vmode & FB_VMODE_INTERLACED)
		par->vBackPorch += (par->vBackPorch % 2);
	if (info->var.vmode & FB_VMODE_DOUBLE) {
		par->vBackPorch <<= 1;
		par->yDim <<=1;
		par->vSyncOn <<=1;
		par->vSyncOff <<=1;
	}

	if (IS_VOODOO2(par)) {
		/* voodoo2 has 32 pixel wide tiles , BUT stange things
		   happen with odd number of tiles */
		par->tiles_in_X = (info->var.xres + 63 ) / 64 * 2;
	} else {
		/* voodoo1 has 64 pixels wide tiles. */
		par->tiles_in_X = (info->var.xres + 63 ) / 64;
	}

	f_ddprintk("hsync_len hSyncOff vsync_len vSyncOff\n");
	f_ddprintk("%-7d %-8d %-7d %-8d\n",
	           info->var.hsync_len, par->hSyncOff,
	           par->vSyncOn, par->vSyncOff);
	f_ddprintk("left_margin upper_margin xres yres Freq\n");
	f_ddprintk("%-10d %-10d %-4d %-4d %-8ld\n",
	           info->var.left_margin, info->var.upper_margin,
	           info->var.xres, info->var.yres, PICOS2KHZ(info->var.pixclock));

	sst_write(NOPCMD, 0);
	sst_wait_idle();
	pci_write_config_dword(sst_dev, PCI_INIT_ENABLE, PCI_EN_INIT_WR);
	sst_set_bits(FBIINIT1, VIDEO_RESET);
	sst_set_bits(FBIINIT0, FBI_RESET | FIFO_RESET);
	sst_unset_bits(FBIINIT2, EN_DRAM_REFRESH);
	sst_wait_idle();

	/*sst_unset_bits (FBIINIT0, FBI_RESET); / reenable FBI ? */

	sst_write(BACKPORCH, par->vBackPorch << 16 | (info->var.left_margin - 2));
	sst_write(VIDEODIMENSIONS, par->yDim << 16 | (info->var.xres - 1));
	sst_write(HSYNC, (par->hSyncOff - 1) << 16 | (info->var.hsync_len - 1));
	sst_write(VSYNC,       par->vSyncOff << 16 | par->vSyncOn);

	fbiinit2 = sst_read(FBIINIT2);
	fbiinit3 = sst_read(FBIINIT3);

	/* everything is reset. we enable fbiinit2/3 remap : dac acces ok */
	pci_write_config_dword(sst_dev, PCI_INIT_ENABLE,
	                       PCI_EN_INIT_WR | PCI_REMAP_DAC );

	par->dac_sw.set_vidmod(info, info->var.bits_per_pixel);

	/* set video clock */
	par->dac_sw.set_pll(info, &par->pll, VID_CLOCK);

	/* disable fbiinit2/3 remap */
	pci_write_config_dword(sst_dev, PCI_INIT_ENABLE,
	                       PCI_EN_INIT_WR);

	/* restore fbiinit2/3 */
	sst_write(FBIINIT2,fbiinit2);
	sst_write(FBIINIT3,fbiinit3);

	fbiinit1 = (sst_read(FBIINIT1) & VIDEO_MASK)
	            | EN_DATA_OE
	            | EN_BLANK_OE
	            | EN_HVSYNC_OE
	            | EN_DCLK_OE
		 /* | (15 << TILES_IN_X_SHIFT) */
	            | SEL_INPUT_VCLK_2X
		 /* | (2 << VCLK_2X_SEL_DEL_SHIFT)
	            | (2 << VCLK_DEL_SHIFT) */;
/* try with vclk_in_delay =0 (bits 29:30) , vclk_out_delay =0 (bits(27:28)
 in (near) future set them accordingly to revision + resolution (cf glide)
 first understand what it stands for :)
 FIXME: there are some artefacts... check for the vclk_in_delay
 lets try with 6ns delay in both vclk_out & in...
 doh... they're still there :\
*/

	ntiles = par->tiles_in_X;
	if (IS_VOODOO2(par)) {
		fbiinit1 |= ((ntiles & 0x20) >> 5) << TILES_IN_X_MSB_SHIFT
		            | ((ntiles & 0x1e) >> 1) << TILES_IN_X_SHIFT;
/* as the only value of importance for us in fbiinit6 is tiles in X (lsb),
   and as reading fbinit 6 will return crap (see FBIINIT6_DEFAULT) we just
   write our value. BTW due to the dac unable to read odd number of tiles, this
   field is always null ... */
		fbiinit6 = (ntiles & 0x1) << TILES_IN_X_LSB_SHIFT;
	}
	else
		fbiinit1 |= ntiles << TILES_IN_X_SHIFT;

	switch (info->var.bits_per_pixel) {
	case 16:
		fbiinit1 |=  SEL_SOURCE_VCLK_2X_SEL;
		break;
	default:
		return -EINVAL;
	}
	sst_write(FBIINIT1, fbiinit1);
	if (IS_VOODOO2(par)) {
		sst_write(FBIINIT6, fbiinit6);
		fbiinit5=sst_read(FBIINIT5) & FBIINIT5_MASK ;
		if (info->var.vmode & FB_VMODE_INTERLACED)
			fbiinit5 |= INTERLACE;
		if (info->var.vmode & FB_VMODE_DOUBLE)
			fbiinit5 |= VDOUBLESCAN;
		if (info->var.sync & FB_SYNC_HOR_HIGH_ACT)
			fbiinit5 |= HSYNC_HIGH;
		if (info->var.sync & FB_SYNC_VERT_HIGH_ACT)
			fbiinit5 |= VSYNC_HIGH;
		sst_write(FBIINIT5, fbiinit5);
	}
	sst_wait_idle();
	sst_unset_bits(FBIINIT1, VIDEO_RESET);
	sst_unset_bits(FBIINIT0, FBI_RESET | FIFO_RESET);
	sst_set_bits(FBIINIT2, EN_DRAM_REFRESH);
	/* disables fbiinit writes */
	pci_write_config_dword(sst_dev, PCI_INIT_ENABLE, PCI_EN_FIFO_WR);

	/* set lfbmode : set mode + front buffer for reads/writes
	   + disable pipeline */
	switch (info->var.bits_per_pixel) {
	case 16:
		lfbmode = LFB_565;
		break;
	default:
		return -EINVAL;
	}

#if defined(__BIG_ENDIAN)
	/* Enable byte-swizzle functionality in hardware.
	 * With this enabled, all our read- and write-accesses to
	 * the voodoo framebuffer can be done in native format, and
	 * the hardware will automatically convert it to little-endian.
	 * - tested on HP-PARISC, Helge Deller <deller@gmx.de> */
	lfbmode |= ( LFB_WORD_SWIZZLE_WR | LFB_BYTE_SWIZZLE_WR |
		     LFB_WORD_SWIZZLE_RD | LFB_BYTE_SWIZZLE_RD );
#endif
	
	if (clipping) {
		sst_write(LFBMODE, lfbmode | EN_PXL_PIPELINE);
	/*
	 * Set "clipping" dimensions. If clipping is disabled and
	 * writes to offscreen areas of the framebuffer are performed,
	 * the "behaviour is undefined" (_very_ undefined) - Urs
	 */
	/* btw, it requires enabling pixel pipeline in LFBMODE .
	   off screen read/writes will just wrap and read/print pixels
	   on screen. Ugly but not that dangerous */
		f_ddprintk("setting clipping dimensions 0..%d, 0..%d\n",
		            info->var.xres - 1, par->yDim - 1);

		sst_write(CLIP_LEFT_RIGHT, info->var.xres);
		sst_write(CLIP_LOWY_HIGHY, par->yDim);
		sst_set_bits(FBZMODE, EN_CLIPPING | EN_RGB_WRITE);
	} else {
		/* no clipping : direct access, no pipeline */
		sst_write(LFBMODE, lfbmode);
	}
	return 0;
}