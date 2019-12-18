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
struct nv04_mode_state {void* sel_clk; void* pllsel; struct nv04_crtc_reg* crtc_reg; } ;
struct nv04_crtc_reg {int fp_debug_0; void** ctv_regs; void* ramdac_a34; void* ramdac_a24; void* ramdac_a20; void* ramdac_8c0; void* fp_margin_color; void* fp_debug_2; void* fp_debug_1; void* fp_control; void** dither_regs; void* dither; void** fp_horiz_regs; void** fp_vert_regs; void* tv_hsync_delay2; void* tv_hsync_delay; void* tv_hskew; void* tv_htotal; void* tv_vsync_delay; void* tv_vskew; void* tv_vtotal; void* tv_setup; void* ramdac_634; void* ramdac_630; void* ramdac_gen_ctrl; int /*<<< orphan*/  pllvals; void* nv10_cursync; } ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ card_type; int chipset; } ;

/* Variables and functions */
 void* NVReadRAMDAC (struct drm_device*,int,scalar_t__) ; 
 int /*<<< orphan*/  NVWriteRAMDAC (struct drm_device*,int /*<<< orphan*/ ,scalar_t__,int) ; 
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
 int NV_PRAMDAC_FP_DEBUG_0_PWRDOWN_FPCLK ; 
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
 scalar_t__ NV_RAMDAC_DITHER_NV11 ; 
 scalar_t__ NV_RAMDAC_FP_DITHER ; 
 scalar_t__ NV_RAMDAC_NV10_CURSYNC ; 
 int /*<<< orphan*/  PLL_VPLL0 ; 
 int /*<<< orphan*/  PLL_VPLL1 ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_hw_get_pllvals (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* nv_device (int /*<<< orphan*/ ) ; 
 scalar_t__ nv_gf4_disp_arch (struct drm_device*) ; 
 scalar_t__ nv_two_heads (struct drm_device*) ; 

__attribute__((used)) static void
nv_save_state_ramdac(struct drm_device *dev, int head,
		     struct nv04_mode_state *state)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nv04_crtc_reg *regp = &state->crtc_reg[head];
	int i;

	if (nv_device(drm->device)->card_type >= NV_10)
		regp->nv10_cursync = NVReadRAMDAC(dev, head, NV_RAMDAC_NV10_CURSYNC);

	nouveau_hw_get_pllvals(dev, head ? PLL_VPLL1 : PLL_VPLL0, &regp->pllvals);
	state->pllsel = NVReadRAMDAC(dev, 0, NV_PRAMDAC_PLL_COEFF_SELECT);
	if (nv_two_heads(dev))
		state->sel_clk = NVReadRAMDAC(dev, 0, NV_PRAMDAC_SEL_CLK);
	if (nv_device(drm->device)->chipset == 0x11)
		regp->dither = NVReadRAMDAC(dev, head, NV_RAMDAC_DITHER_NV11);

	regp->ramdac_gen_ctrl = NVReadRAMDAC(dev, head, NV_PRAMDAC_GENERAL_CONTROL);

	if (nv_gf4_disp_arch(dev))
		regp->ramdac_630 = NVReadRAMDAC(dev, head, NV_PRAMDAC_630);
	if (nv_device(drm->device)->chipset >= 0x30)
		regp->ramdac_634 = NVReadRAMDAC(dev, head, NV_PRAMDAC_634);

	regp->tv_setup = NVReadRAMDAC(dev, head, NV_PRAMDAC_TV_SETUP);
	regp->tv_vtotal = NVReadRAMDAC(dev, head, NV_PRAMDAC_TV_VTOTAL);
	regp->tv_vskew = NVReadRAMDAC(dev, head, NV_PRAMDAC_TV_VSKEW);
	regp->tv_vsync_delay = NVReadRAMDAC(dev, head, NV_PRAMDAC_TV_VSYNC_DELAY);
	regp->tv_htotal = NVReadRAMDAC(dev, head, NV_PRAMDAC_TV_HTOTAL);
	regp->tv_hskew = NVReadRAMDAC(dev, head, NV_PRAMDAC_TV_HSKEW);
	regp->tv_hsync_delay = NVReadRAMDAC(dev, head, NV_PRAMDAC_TV_HSYNC_DELAY);
	regp->tv_hsync_delay2 = NVReadRAMDAC(dev, head, NV_PRAMDAC_TV_HSYNC_DELAY2);

	for (i = 0; i < 7; i++) {
		uint32_t ramdac_reg = NV_PRAMDAC_FP_VDISPLAY_END + (i * 4);
		regp->fp_vert_regs[i] = NVReadRAMDAC(dev, head, ramdac_reg);
		regp->fp_horiz_regs[i] = NVReadRAMDAC(dev, head, ramdac_reg + 0x20);
	}

	if (nv_gf4_disp_arch(dev)) {
		regp->dither = NVReadRAMDAC(dev, head, NV_RAMDAC_FP_DITHER);
		for (i = 0; i < 3; i++) {
			regp->dither_regs[i] = NVReadRAMDAC(dev, head, NV_PRAMDAC_850 + i * 4);
			regp->dither_regs[i + 3] = NVReadRAMDAC(dev, head, NV_PRAMDAC_85C + i * 4);
		}
	}

	regp->fp_control = NVReadRAMDAC(dev, head, NV_PRAMDAC_FP_TG_CONTROL);
	regp->fp_debug_0 = NVReadRAMDAC(dev, head, NV_PRAMDAC_FP_DEBUG_0);
	if (!nv_gf4_disp_arch(dev) && head == 0) {
		/* early chips don't allow access to PRAMDAC_TMDS_* without
		 * the head A FPCLK on (nv11 even locks up) */
		NVWriteRAMDAC(dev, 0, NV_PRAMDAC_FP_DEBUG_0, regp->fp_debug_0 &
			      ~NV_PRAMDAC_FP_DEBUG_0_PWRDOWN_FPCLK);
	}
	regp->fp_debug_1 = NVReadRAMDAC(dev, head, NV_PRAMDAC_FP_DEBUG_1);
	regp->fp_debug_2 = NVReadRAMDAC(dev, head, NV_PRAMDAC_FP_DEBUG_2);

	regp->fp_margin_color = NVReadRAMDAC(dev, head, NV_PRAMDAC_FP_MARGIN_COLOR);

	if (nv_gf4_disp_arch(dev))
		regp->ramdac_8c0 = NVReadRAMDAC(dev, head, NV_PRAMDAC_8C0);

	if (nv_device(drm->device)->card_type == NV_40) {
		regp->ramdac_a20 = NVReadRAMDAC(dev, head, NV_PRAMDAC_A20);
		regp->ramdac_a24 = NVReadRAMDAC(dev, head, NV_PRAMDAC_A24);
		regp->ramdac_a34 = NVReadRAMDAC(dev, head, NV_PRAMDAC_A34);

		for (i = 0; i < 38; i++)
			regp->ctv_regs[i] = NVReadRAMDAC(dev, head,
							 NV_PRAMDAC_CTV + 4*i);
	}
}