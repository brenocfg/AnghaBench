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
typedef  int u32 ;
struct TYPE_5__ {int bits_per_pixel; int xres_virtual; } ;
struct TYPE_4__ {int line_length; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ fix; } ;
struct TYPE_6__ {int vyres; int dp_pix_width; int dp_chain_mask; } ;
struct atyfb_par {TYPE_3__ crtc; } ;

/* Variables and functions */
 int BKGD_MIX_D ; 
 int /*<<< orphan*/  CLR_CMP_CLR ; 
 int /*<<< orphan*/  CLR_CMP_CNTL ; 
 int /*<<< orphan*/  CLR_CMP_MASK ; 
 int /*<<< orphan*/  CONTEXT_MASK ; 
 int /*<<< orphan*/  CRTC_INT_CNTL ; 
 int /*<<< orphan*/  DP_BKGD_CLR ; 
 int /*<<< orphan*/  DP_CHAIN_MASK ; 
 int /*<<< orphan*/  DP_FRGD_CLR ; 
 int /*<<< orphan*/  DP_MIX ; 
 int /*<<< orphan*/  DP_PIX_WIDTH ; 
 int /*<<< orphan*/  DP_SRC ; 
 int /*<<< orphan*/  DP_WRITE_MASK ; 
 int /*<<< orphan*/  DST_BRES_DEC ; 
 int /*<<< orphan*/  DST_BRES_ERR ; 
 int /*<<< orphan*/  DST_BRES_INC ; 
 int /*<<< orphan*/  DST_CNTL ; 
 int /*<<< orphan*/  DST_HEIGHT ; 
 int DST_LAST_PEL ; 
 int /*<<< orphan*/  DST_OFF_PITCH ; 
 int DST_X_LEFT_TO_RIGHT ; 
 int DST_Y_TOP_TO_BOTTOM ; 
 int /*<<< orphan*/  DST_Y_X ; 
 int FRGD_MIX_S ; 
 int FRGD_SRC_FRGD_CLR ; 
 int /*<<< orphan*/  GUI_TRAJ_CNTL ; 
 int /*<<< orphan*/  HOST_CNTL ; 
 scalar_t__ M64_HAS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_VGA_RP_SEL ; 
 int /*<<< orphan*/  MEM_VGA_WP_SEL ; 
 int /*<<< orphan*/  PAT_CNTL ; 
 int /*<<< orphan*/  PAT_REG0 ; 
 int /*<<< orphan*/  PAT_REG1 ; 
 int /*<<< orphan*/  RESET_3D ; 
 int /*<<< orphan*/  SCALE_3D_CNTL ; 
 int /*<<< orphan*/  SC_BOTTOM ; 
 int /*<<< orphan*/  SC_LEFT ; 
 int /*<<< orphan*/  SC_RIGHT ; 
 int /*<<< orphan*/  SC_TOP ; 
 int /*<<< orphan*/  SRC_CNTL ; 
 int /*<<< orphan*/  SRC_HEIGHT1_WIDTH1 ; 
 int /*<<< orphan*/  SRC_HEIGHT2_WIDTH2 ; 
 int SRC_LINE_X_LEFT_TO_RIGHT ; 
 int /*<<< orphan*/  SRC_OFF_PITCH ; 
 int /*<<< orphan*/  SRC_Y_X ; 
 int /*<<< orphan*/  SRC_Y_X_START ; 
 int /*<<< orphan*/  Z_CNTL ; 
 int aty_ld_le32 (int /*<<< orphan*/ ,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_reset_engine (struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_st_le32 (int /*<<< orphan*/ ,int,struct atyfb_par*) ; 
 int /*<<< orphan*/  reset_GTC_3D_engine (struct atyfb_par*) ; 
 int /*<<< orphan*/  wait_for_fifo (int,struct atyfb_par*) ; 
 int /*<<< orphan*/  wait_for_idle (struct atyfb_par*) ; 

void aty_init_engine(struct atyfb_par *par, struct fb_info *info)
{
	u32 pitch_value;
	u32 vxres;

	/* determine modal information from global mode structure */
	pitch_value = info->fix.line_length / (info->var.bits_per_pixel / 8);
	vxres = info->var.xres_virtual;

	if (info->var.bits_per_pixel == 24) {
		/* In 24 bpp, the engine is in 8 bpp - this requires that all */
		/* horizontal coordinates and widths must be adjusted */
		pitch_value *= 3;
		vxres *= 3;
	}

	/* On GTC (RagePro), we need to reset the 3D engine before */
	if (M64_HAS(RESET_3D))
		reset_GTC_3D_engine(par);

	/* Reset engine, enable, and clear any engine errors */
	aty_reset_engine(par);
	/* Ensure that vga page pointers are set to zero - the upper */
	/* page pointers are set to 1 to handle overflows in the */
	/* lower page */
	aty_st_le32(MEM_VGA_WP_SEL, 0x00010000, par);
	aty_st_le32(MEM_VGA_RP_SEL, 0x00010000, par);

	/* ---- Setup standard engine context ---- */

	/* All GUI registers here are FIFOed - therefore, wait for */
	/* the appropriate number of empty FIFO entries */
	wait_for_fifo(14, par);

	/* enable all registers to be loaded for context loads */
	aty_st_le32(CONTEXT_MASK, 0xFFFFFFFF, par);

	/* set destination pitch to modal pitch, set offset to zero */
	aty_st_le32(DST_OFF_PITCH, (pitch_value / 8) << 22, par);

	/* zero these registers (set them to a known state) */
	aty_st_le32(DST_Y_X, 0, par);
	aty_st_le32(DST_HEIGHT, 0, par);
	aty_st_le32(DST_BRES_ERR, 0, par);
	aty_st_le32(DST_BRES_INC, 0, par);
	aty_st_le32(DST_BRES_DEC, 0, par);

	/* set destination drawing attributes */
	aty_st_le32(DST_CNTL, DST_LAST_PEL | DST_Y_TOP_TO_BOTTOM |
		    DST_X_LEFT_TO_RIGHT, par);

	/* set source pitch to modal pitch, set offset to zero */
	aty_st_le32(SRC_OFF_PITCH, (pitch_value / 8) << 22, par);

	/* set these registers to a known state */
	aty_st_le32(SRC_Y_X, 0, par);
	aty_st_le32(SRC_HEIGHT1_WIDTH1, 1, par);
	aty_st_le32(SRC_Y_X_START, 0, par);
	aty_st_le32(SRC_HEIGHT2_WIDTH2, 1, par);

	/* set source pixel retrieving attributes */
	aty_st_le32(SRC_CNTL, SRC_LINE_X_LEFT_TO_RIGHT, par);

	/* set host attributes */
	wait_for_fifo(13, par);
	aty_st_le32(HOST_CNTL, 0, par);

	/* set pattern attributes */
	aty_st_le32(PAT_REG0, 0, par);
	aty_st_le32(PAT_REG1, 0, par);
	aty_st_le32(PAT_CNTL, 0, par);

	/* set scissors to modal size */
	aty_st_le32(SC_LEFT, 0, par);
	aty_st_le32(SC_TOP, 0, par);
	aty_st_le32(SC_BOTTOM, par->crtc.vyres - 1, par);
	aty_st_le32(SC_RIGHT, vxres - 1, par);

	/* set background color to minimum value (usually BLACK) */
	aty_st_le32(DP_BKGD_CLR, 0, par);

	/* set foreground color to maximum value (usually WHITE) */
	aty_st_le32(DP_FRGD_CLR, 0xFFFFFFFF, par);

	/* set write mask to effect all pixel bits */
	aty_st_le32(DP_WRITE_MASK, 0xFFFFFFFF, par);

	/* set foreground mix to overpaint and background mix to */
	/* no-effect */
	aty_st_le32(DP_MIX, FRGD_MIX_S | BKGD_MIX_D, par);

	/* set primary source pixel channel to foreground color */
	/* register */
	aty_st_le32(DP_SRC, FRGD_SRC_FRGD_CLR, par);

	/* set compare functionality to false (no-effect on */
	/* destination) */
	wait_for_fifo(3, par);
	aty_st_le32(CLR_CMP_CLR, 0, par);
	aty_st_le32(CLR_CMP_MASK, 0xFFFFFFFF, par);
	aty_st_le32(CLR_CMP_CNTL, 0, par);

	/* set pixel depth */
	wait_for_fifo(2, par);
	aty_st_le32(DP_PIX_WIDTH, par->crtc.dp_pix_width, par);
	aty_st_le32(DP_CHAIN_MASK, par->crtc.dp_chain_mask, par);

	wait_for_fifo(5, par);
 	aty_st_le32(SCALE_3D_CNTL, 0, par);
	aty_st_le32(Z_CNTL, 0, par);
	aty_st_le32(CRTC_INT_CNTL, aty_ld_le32(CRTC_INT_CNTL, par) & ~0x20,
		    par);
	aty_st_le32(GUI_TRAJ_CNTL, 0x100023, par);

	/* insure engine is idle before leaving */
	wait_for_idle(par);
}