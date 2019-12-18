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
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct nouveau_crtc {int /*<<< orphan*/  index; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_display_mode {int /*<<< orphan*/  clock; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  sel_clk; } ;
struct TYPE_6__ {TYPE_1__ mode_reg; } ;
struct TYPE_5__ {scalar_t__ card_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVWriteRAMDAC (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NV_40 ; 
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_PRAMDAC_SEL_CLK ; 
 int /*<<< orphan*/  drm_mode_debug_printmodeline (struct drm_display_mode*) ; 
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 TYPE_3__* nv04_display (struct drm_device*) ; 
 int /*<<< orphan*/  nv_crtc_calc_state_ext (struct drm_crtc*,struct drm_display_mode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_crtc_mode_set_regs (struct drm_crtc*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  nv_crtc_mode_set_vga (struct drm_crtc*,struct drm_display_mode*) ; 
 TYPE_2__* nv_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_lock_vga_crtc_shadow (struct drm_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nv_crtc_mode_set(struct drm_crtc *crtc, struct drm_display_mode *mode,
		 struct drm_display_mode *adjusted_mode,
		 int x, int y, struct drm_framebuffer *old_fb)
{
	struct drm_device *dev = crtc->dev;
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	struct nouveau_drm *drm = nouveau_drm(dev);

	NV_DEBUG(drm, "CTRC mode on CRTC %d:\n", nv_crtc->index);
	drm_mode_debug_printmodeline(adjusted_mode);

	/* unlock must come after turning off FP_TG_CONTROL in output_prepare */
	nv_lock_vga_crtc_shadow(dev, nv_crtc->index, -1);

	nv_crtc_mode_set_vga(crtc, adjusted_mode);
	/* calculated in nv04_dfp_prepare, nv40 needs it written before calculating PLLs */
	if (nv_device(drm->device)->card_type == NV_40)
		NVWriteRAMDAC(dev, 0, NV_PRAMDAC_SEL_CLK, nv04_display(dev)->mode_reg.sel_clk);
	nv_crtc_mode_set_regs(crtc, adjusted_mode);
	nv_crtc_calc_state_ext(crtc, mode, adjusted_mode->clock);
	return 0;
}