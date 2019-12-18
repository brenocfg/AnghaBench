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
typedef  scalar_t__ uint32_t ;
struct nv04_mode_state {int /*<<< orphan*/  sel_clk; int /*<<< orphan*/  pllsel; struct nv04_crtc_reg* crtc_reg; } ;
struct nv04_crtc_reg {int /*<<< orphan*/ * ctv_regs; int /*<<< orphan*/  ramdac_a34; int /*<<< orphan*/  ramdac_a24; int /*<<< orphan*/  ramdac_a20; int /*<<< orphan*/  ramdac_8c0; int /*<<< orphan*/  fp_margin_color; int /*<<< orphan*/  fp_debug_2; int /*<<< orphan*/  fp_debug_1; int /*<<< orphan*/  fp_debug_0; int /*<<< orphan*/  fp_control; int /*<<< orphan*/ * dither_regs; int /*<<< orphan*/  dither; int /*<<< orphan*/ * fp_horiz_regs; int /*<<< orphan*/ * fp_vert_regs; int /*<<< orphan*/  tv_hsync_delay2; int /*<<< orphan*/  tv_hsync_delay; int /*<<< orphan*/  tv_hskew; int /*<<< orphan*/  tv_htotal; int /*<<< orphan*/  tv_vsync_delay; int /*<<< orphan*/  tv_vskew; int /*<<< orphan*/  tv_vtotal; int /*<<< orphan*/  tv_setup; int /*<<< orphan*/  ramdac_634; int /*<<< orphan*/  ramdac_630; int /*<<< orphan*/  ramdac_gen_ctrl; int /*<<< orphan*/  pllvals; int /*<<< orphan*/  nv10_cursync; } ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct nouveau_clock {int /*<<< orphan*/  (* pll_prog ) (struct nouveau_clock*,scalar_t__,int /*<<< orphan*/ *) ;} ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ card_type; int chipset; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVWriteRAMDAC (struct drm_device*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ NV_10 ; 
 scalar_t__ NV_40 ; 
 scalar_t__ NV_PRAMDAC_630 ; 
 scalar_t__ NV_PRAMDAC_634 ; 
 scalar_t__ NV_PRAMDAC_850 ; 
 scalar_t__ NV_PRAMDAC_85C ; 
 scalar_t__ NV_PRAMDAC_8C0 ; 
 scalar_t__ NV_PRAMDAC_A20 ; 
 scalar_t__ NV_PRAMDAC_A24 ; 
 scalar_t__ NV_PRAMDAC_A34 ; 
 scalar_t__ NV_PRAMDAC_CTV ; 
 scalar_t__ NV_PRAMDAC_FP_DEBUG_0 ; 
 scalar_t__ NV_PRAMDAC_FP_DEBUG_1 ; 
 scalar_t__ NV_PRAMDAC_FP_DEBUG_2 ; 
 scalar_t__ NV_PRAMDAC_FP_MARGIN_COLOR ; 
 scalar_t__ NV_PRAMDAC_FP_TG_CONTROL ; 
 scalar_t__ NV_PRAMDAC_FP_VDISPLAY_END ; 
 scalar_t__ NV_PRAMDAC_GENERAL_CONTROL ; 
 scalar_t__ NV_PRAMDAC_PLL_COEFF_SELECT ; 
 scalar_t__ NV_PRAMDAC_SEL_CLK ; 
 scalar_t__ NV_PRAMDAC_TV_HSKEW ; 
 scalar_t__ NV_PRAMDAC_TV_HSYNC_DELAY ; 
 scalar_t__ NV_PRAMDAC_TV_HSYNC_DELAY2 ; 
 scalar_t__ NV_PRAMDAC_TV_HTOTAL ; 
 scalar_t__ NV_PRAMDAC_TV_SETUP ; 
 scalar_t__ NV_PRAMDAC_TV_VSKEW ; 
 scalar_t__ NV_PRAMDAC_TV_VSYNC_DELAY ; 
 scalar_t__ NV_PRAMDAC_TV_VTOTAL ; 
 scalar_t__ NV_PRAMDAC_VPLL_COEFF ; 
 scalar_t__ NV_RAMDAC_DITHER_NV11 ; 
 scalar_t__ NV_RAMDAC_FP_DITHER ; 
 scalar_t__ NV_RAMDAC_NV10_CURSYNC ; 
 scalar_t__ NV_RAMDAC_VPLL2 ; 
 struct nouveau_clock* nouveau_clock (int /*<<< orphan*/ ) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 TYPE_1__* nv_device (int /*<<< orphan*/ ) ; 
 scalar_t__ nv_gf4_disp_arch (struct drm_device*) ; 
 scalar_t__ nv_two_heads (struct drm_device*) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_clock*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nv_load_state_ramdac(struct drm_device *dev, int head,
		     struct nv04_mode_state *state)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_clock *clk = nouveau_clock(drm->device);
	struct nv04_crtc_reg *regp = &state->crtc_reg[head];
	uint32_t pllreg = head ? NV_RAMDAC_VPLL2 : NV_PRAMDAC_VPLL_COEFF;
	int i;

	if (nv_device(drm->device)->card_type >= NV_10)
		NVWriteRAMDAC(dev, head, NV_RAMDAC_NV10_CURSYNC, regp->nv10_cursync);

	clk->pll_prog(clk, pllreg, &regp->pllvals);
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_PLL_COEFF_SELECT, state->pllsel);
	if (nv_two_heads(dev))
		NVWriteRAMDAC(dev, 0, NV_PRAMDAC_SEL_CLK, state->sel_clk);
	if (nv_device(drm->device)->chipset == 0x11)
		NVWriteRAMDAC(dev, head, NV_RAMDAC_DITHER_NV11, regp->dither);

	NVWriteRAMDAC(dev, head, NV_PRAMDAC_GENERAL_CONTROL, regp->ramdac_gen_ctrl);

	if (nv_gf4_disp_arch(dev))
		NVWriteRAMDAC(dev, head, NV_PRAMDAC_630, regp->ramdac_630);
	if (nv_device(drm->device)->chipset >= 0x30)
		NVWriteRAMDAC(dev, head, NV_PRAMDAC_634, regp->ramdac_634);

	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TV_SETUP, regp->tv_setup);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TV_VTOTAL, regp->tv_vtotal);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TV_VSKEW, regp->tv_vskew);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TV_VSYNC_DELAY, regp->tv_vsync_delay);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TV_HTOTAL, regp->tv_htotal);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TV_HSKEW, regp->tv_hskew);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TV_HSYNC_DELAY, regp->tv_hsync_delay);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TV_HSYNC_DELAY2, regp->tv_hsync_delay2);

	for (i = 0; i < 7; i++) {
		uint32_t ramdac_reg = NV_PRAMDAC_FP_VDISPLAY_END + (i * 4);

		NVWriteRAMDAC(dev, head, ramdac_reg, regp->fp_vert_regs[i]);
		NVWriteRAMDAC(dev, head, ramdac_reg + 0x20, regp->fp_horiz_regs[i]);
	}

	if (nv_gf4_disp_arch(dev)) {
		NVWriteRAMDAC(dev, head, NV_RAMDAC_FP_DITHER, regp->dither);
		for (i = 0; i < 3; i++) {
			NVWriteRAMDAC(dev, head, NV_PRAMDAC_850 + i * 4, regp->dither_regs[i]);
			NVWriteRAMDAC(dev, head, NV_PRAMDAC_85C + i * 4, regp->dither_regs[i + 3]);
		}
	}

	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_TG_CONTROL, regp->fp_control);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_DEBUG_0, regp->fp_debug_0);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_DEBUG_1, regp->fp_debug_1);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_DEBUG_2, regp->fp_debug_2);

	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_MARGIN_COLOR, regp->fp_margin_color);

	if (nv_gf4_disp_arch(dev))
		NVWriteRAMDAC(dev, head, NV_PRAMDAC_8C0, regp->ramdac_8c0);

	if (nv_device(drm->device)->card_type == NV_40) {
		NVWriteRAMDAC(dev, head, NV_PRAMDAC_A20, regp->ramdac_a20);
		NVWriteRAMDAC(dev, head, NV_PRAMDAC_A24, regp->ramdac_a24);
		NVWriteRAMDAC(dev, head, NV_PRAMDAC_A34, regp->ramdac_a34);

		for (i = 0; i < 38; i++)
			NVWriteRAMDAC(dev, head,
				      NV_PRAMDAC_CTV + 4*i, regp->ctv_regs[i]);
	}
}