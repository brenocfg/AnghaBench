#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int width; int height; } ;
struct gbefb_par {TYPE_3__ timing; } ;
struct TYPE_7__ {int line_length; void* visual; } ;
struct TYPE_11__ {int bits_per_pixel; int xres_virtual; } ;
struct fb_info {TYPE_1__ fix; TYPE_5__ var; scalar_t__ par; } ;
struct TYPE_10__ {unsigned int* mode_regs; int vt_intr01; int vt_intr23; unsigned int frm_control; unsigned int frm_size_tile; unsigned int frm_size_pixel; int* gmap; scalar_t__ crs_ctl; scalar_t__ ovr_width_tile; scalar_t__ did_control; } ;
struct TYPE_8__ {int dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF ; 
 int /*<<< orphan*/  FB_HEIGHT_PIX ; 
 void* FB_VISUAL_PSEUDOCOLOR ; 
 void* FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  FRM_CONTROL ; 
 int /*<<< orphan*/  FRM_DEPTH ; 
 int /*<<< orphan*/  FRM_DMA_ENABLE ; 
 int /*<<< orphan*/  FRM_LINEAR ; 
 int /*<<< orphan*/  FRM_RHS ; 
 int /*<<< orphan*/  FRM_SIZE_PIXEL ; 
 int /*<<< orphan*/  FRM_SIZE_TILE ; 
 int /*<<< orphan*/  FRM_TILE_PTR ; 
 int /*<<< orphan*/  FRM_WIDTH_TILE ; 
 int GBE_BMODE_BOTH ; 
 int GBE_CMODE_ARGB5 ; 
 int GBE_CMODE_I8 ; 
 int GBE_CMODE_RGB8 ; 
 int GBE_FRM_DEPTH_16 ; 
 int GBE_FRM_DEPTH_32 ; 
 int GBE_FRM_DEPTH_8 ; 
 int /*<<< orphan*/  SET_GBE_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  TYP ; 
 int /*<<< orphan*/  WID ; 
 int /*<<< orphan*/  compute_gbe_timing (TYPE_5__*,TYPE_3__*) ; 
 TYPE_4__* gbe ; 
 int* gbe_cmap ; 
 int /*<<< orphan*/  gbe_loadcmap () ; 
 int /*<<< orphan*/  gbe_set_timing_info (TYPE_3__*) ; 
 TYPE_2__ gbe_tiles ; 
 int /*<<< orphan*/  gbe_turn_off () ; 
 int /*<<< orphan*/  gbe_turn_on () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int gbefb_set_par(struct fb_info *info)
{
	int i;
	unsigned int val;
	int wholeTilesX, partTilesX, maxPixelsPerTileX;
	int height_pix;
	int xpmax, ypmax;	/* Monitor resolution */
	int bytesPerPixel;	/* Bytes per pixel */
	struct gbefb_par *par = (struct gbefb_par *) info->par;

	compute_gbe_timing(&info->var, &par->timing);

	bytesPerPixel = info->var.bits_per_pixel / 8;
	info->fix.line_length = info->var.xres_virtual * bytesPerPixel;
	xpmax = par->timing.width;
	ypmax = par->timing.height;

	/* turn off GBE */
	gbe_turn_off();

	/* set timing info */
	gbe_set_timing_info(&par->timing);

	/* initialize DIDs */
	val = 0;
	switch (bytesPerPixel) {
	case 1:
		SET_GBE_FIELD(WID, TYP, val, GBE_CMODE_I8);
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		break;
	case 2:
		SET_GBE_FIELD(WID, TYP, val, GBE_CMODE_ARGB5);
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		break;
	case 4:
		SET_GBE_FIELD(WID, TYP, val, GBE_CMODE_RGB8);
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		break;
	}
	SET_GBE_FIELD(WID, BUF, val, GBE_BMODE_BOTH);

	for (i = 0; i < 32; i++)
		gbe->mode_regs[i] = val;

	/* Initialize interrupts */
	gbe->vt_intr01 = 0xffffffff;
	gbe->vt_intr23 = 0xffffffff;

	/* HACK:
	   The GBE hardware uses a tiled memory to screen mapping. Tiles are
	   blocks of 512x128, 256x128 or 128x128 pixels, respectively for 8bit,
	   16bit and 32 bit modes (64 kB). They cover the screen with partial
	   tiles on the right and/or bottom of the screen if needed.
	   For exemple in 640x480 8 bit mode the mapping is:

	   <-------- 640 ----->
	   <---- 512 ----><128|384 offscreen>
	   ^  ^
	   | 128    [tile 0]        [tile 1]
	   |  v
	   ^
	   4 128    [tile 2]        [tile 3]
	   8  v
	   0  ^
	   128    [tile 4]        [tile 5]
	   |  v
	   |  ^
	   v  96    [tile 6]        [tile 7]
	   32 offscreen

	   Tiles have the advantage that they can be allocated individually in
	   memory. However, this mapping is not linear at all, which is not
	   really convienient. In order to support linear addressing, the GBE
	   DMA hardware is fooled into thinking the screen is only one tile
	   large and but has a greater height, so that the DMA transfer covers
	   the same region.
	   Tiles are still allocated as independent chunks of 64KB of
	   continuous physical memory and remapped so that the kernel sees the
	   framebuffer as a continuous virtual memory. The GBE tile table is
	   set up so that each tile references one of these 64k blocks:

	   GBE -> tile list    framebuffer           TLB   <------------ CPU
	          [ tile 0 ] -> [ 64KB ]  <- [ 16x 4KB page entries ]     ^
	             ...           ...              ...       linear virtual FB
	          [ tile n ] -> [ 64KB ]  <- [ 16x 4KB page entries ]     v


	   The GBE hardware is then told that the buffer is 512*tweaked_height,
	   with tweaked_height = real_width*real_height/pixels_per_tile.
	   Thus the GBE hardware will scan the first tile, filing the first 64k
	   covered region of the screen, and then will proceed to the next
	   tile, until the whole screen is covered.

	   Here is what would happen at 640x480 8bit:

	   normal tiling               linear
	   ^   11111111111111112222    11111111111111111111  ^
	   128 11111111111111112222    11111111111111111111 102 lines
	       11111111111111112222    11111111111111111111  v
	   V   11111111111111112222    11111111222222222222
	       33333333333333334444    22222222222222222222
	       33333333333333334444    22222222222222222222
	       <      512     >        <  256 >               102*640+256 = 64k

	   NOTE: The only mode for which this is not working is 800x600 8bit,
	   as 800*600/512 = 937.5 which is not integer and thus causes
	   flickering.
	   I guess this is not so important as one can use 640x480 8bit or
	   800x600 16bit anyway.
	 */

	/* Tell gbe about the tiles table location */
	/* tile_ptr -> [ tile 1 ] -> FB mem */
	/*             [ tile 2 ] -> FB mem */
	/*               ...                */
	val = 0;
	SET_GBE_FIELD(FRM_CONTROL, FRM_TILE_PTR, val, gbe_tiles.dma >> 9);
	SET_GBE_FIELD(FRM_CONTROL, FRM_DMA_ENABLE, val, 0); /* do not start */
	SET_GBE_FIELD(FRM_CONTROL, FRM_LINEAR, val, 0);
	gbe->frm_control = val;

	maxPixelsPerTileX = 512 / bytesPerPixel;
	wholeTilesX = 1;
	partTilesX = 0;

	/* Initialize the framebuffer */
	val = 0;
	SET_GBE_FIELD(FRM_SIZE_TILE, FRM_WIDTH_TILE, val, wholeTilesX);
	SET_GBE_FIELD(FRM_SIZE_TILE, FRM_RHS, val, partTilesX);

	switch (bytesPerPixel) {
	case 1:
		SET_GBE_FIELD(FRM_SIZE_TILE, FRM_DEPTH, val,
			      GBE_FRM_DEPTH_8);
		break;
	case 2:
		SET_GBE_FIELD(FRM_SIZE_TILE, FRM_DEPTH, val,
			      GBE_FRM_DEPTH_16);
		break;
	case 4:
		SET_GBE_FIELD(FRM_SIZE_TILE, FRM_DEPTH, val,
			      GBE_FRM_DEPTH_32);
		break;
	}
	gbe->frm_size_tile = val;

	/* compute tweaked height */
	height_pix = xpmax * ypmax / maxPixelsPerTileX;

	val = 0;
	SET_GBE_FIELD(FRM_SIZE_PIXEL, FB_HEIGHT_PIX, val, height_pix);
	gbe->frm_size_pixel = val;

	/* turn off DID and overlay DMA */
	gbe->did_control = 0;
	gbe->ovr_width_tile = 0;

	/* Turn off mouse cursor */
	gbe->crs_ctl = 0;

	/* Turn on GBE */
	gbe_turn_on();

	/* Initialize the gamma map */
	udelay(10);
	for (i = 0; i < 256; i++)
		gbe->gmap[i] = (i << 24) | (i << 16) | (i << 8);

	/* Initialize the color map */
	for (i = 0; i < 256; i++)
		gbe_cmap[i] = (i << 8) | (i << 16) | (i << 24);

	gbe_loadcmap();

	return 0;
}