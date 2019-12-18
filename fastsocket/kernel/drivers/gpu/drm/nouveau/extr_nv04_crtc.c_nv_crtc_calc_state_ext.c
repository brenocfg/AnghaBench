#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int max_freq; } ;
struct nvbios_pll {int /*<<< orphan*/  vco2; TYPE_1__ vco1; } ;
struct nv04_mode_state {int pllsel; struct nv04_crtc_reg* crtc_reg; } ;
struct nouveau_pll_vals {int /*<<< orphan*/  log2P; int /*<<< orphan*/  M1; int /*<<< orphan*/  N1; int /*<<< orphan*/  M2; int /*<<< orphan*/  N2; scalar_t__ NM2; } ;
struct nv04_crtc_reg {struct nouveau_pll_vals pllvals; } ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct TYPE_6__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  (* set_offset ) (struct nouveau_crtc*,int /*<<< orphan*/ ) ;} ;
struct nouveau_crtc {size_t index; TYPE_2__ cursor; } ;
struct nouveau_clock {int /*<<< orphan*/  (* pll_calc ) (struct nouveau_clock*,struct nvbios_pll*,int,struct nouveau_pll_vals*) ;} ;
struct nouveau_bios {int dummy; } ;
struct drm_display_mode {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct TYPE_8__ {struct nv04_mode_state mode_reg; } ;
struct TYPE_7__ {int chipset; scalar_t__ card_type; } ;

/* Variables and functions */
 scalar_t__ NV_40 ; 
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int NV_PRAMDAC_PLL_COEFF_SELECT_SOURCE_PROG_MPLL ; 
 int NV_PRAMDAC_PLL_COEFF_SELECT_SOURCE_PROG_NVPLL ; 
 int NV_PRAMDAC_PLL_COEFF_SELECT_USE_VPLL2_TRUE ; 
 int PLLSEL_TV_MASK ; 
 int PLLSEL_VPLL1_MASK ; 
 int PLLSEL_VPLL2_MASK ; 
 int /*<<< orphan*/  PLL_VPLL0 ; 
 int /*<<< orphan*/  PLL_VPLL1 ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct nouveau_bios* nouveau_bios (int /*<<< orphan*/ ) ; 
 struct nouveau_clock* nouveau_clock (int /*<<< orphan*/ ) ; 
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 TYPE_4__* nv04_display (struct drm_device*) ; 
 TYPE_3__* nv_device (int /*<<< orphan*/ ) ; 
 scalar_t__ nvbios_pll_parse (struct nouveau_bios*,int /*<<< orphan*/ ,struct nvbios_pll*) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_clock*,struct nvbios_pll*,int,struct nouveau_pll_vals*) ; 
 int /*<<< orphan*/  stub2 (struct nouveau_crtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nv_crtc_calc_state_ext(struct drm_crtc *crtc, struct drm_display_mode * mode, int dot_clock)
{
	struct drm_device *dev = crtc->dev;
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_bios *bios = nouveau_bios(drm->device);
	struct nouveau_clock *clk = nouveau_clock(drm->device);
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	struct nv04_mode_state *state = &nv04_display(dev)->mode_reg;
	struct nv04_crtc_reg *regp = &state->crtc_reg[nv_crtc->index];
	struct nouveau_pll_vals *pv = &regp->pllvals;
	struct nvbios_pll pll_lim;

	if (nvbios_pll_parse(bios, nv_crtc->index ? PLL_VPLL1 : PLL_VPLL0,
			    &pll_lim))
		return;

	/* NM2 == 0 is used to determine single stage mode on two stage plls */
	pv->NM2 = 0;

	/* for newer nv4x the blob uses only the first stage of the vpll below a
	 * certain clock.  for a certain nv4b this is 150MHz.  since the max
	 * output frequency of the first stage for this card is 300MHz, it is
	 * assumed the threshold is given by vco1 maxfreq/2
	 */
	/* for early nv4x, specifically nv40 and *some* nv43 (devids 0 and 6,
	 * not 8, others unknown), the blob always uses both plls.  no problem
	 * has yet been observed in allowing the use a single stage pll on all
	 * nv43 however.  the behaviour of single stage use is untested on nv40
	 */
	if (nv_device(drm->device)->chipset > 0x40 && dot_clock <= (pll_lim.vco1.max_freq / 2))
		memset(&pll_lim.vco2, 0, sizeof(pll_lim.vco2));


	if (!clk->pll_calc(clk, &pll_lim, dot_clock, pv))
		return;

	state->pllsel &= PLLSEL_VPLL1_MASK | PLLSEL_VPLL2_MASK | PLLSEL_TV_MASK;

	/* The blob uses this always, so let's do the same */
	if (nv_device(drm->device)->card_type == NV_40)
		state->pllsel |= NV_PRAMDAC_PLL_COEFF_SELECT_USE_VPLL2_TRUE;
	/* again nv40 and some nv43 act more like nv3x as described above */
	if (nv_device(drm->device)->chipset < 0x41)
		state->pllsel |= NV_PRAMDAC_PLL_COEFF_SELECT_SOURCE_PROG_MPLL |
				 NV_PRAMDAC_PLL_COEFF_SELECT_SOURCE_PROG_NVPLL;
	state->pllsel |= nv_crtc->index ? PLLSEL_VPLL2_MASK : PLLSEL_VPLL1_MASK;

	if (pv->NM2)
		NV_DEBUG(drm, "vpll: n1 %d n2 %d m1 %d m2 %d log2p %d\n",
			 pv->N1, pv->N2, pv->M1, pv->M2, pv->log2P);
	else
		NV_DEBUG(drm, "vpll: n %d m %d log2p %d\n",
			 pv->N1, pv->M1, pv->log2P);

	nv_crtc->cursor.set_offset(nv_crtc, nv_crtc->cursor.offset);
}