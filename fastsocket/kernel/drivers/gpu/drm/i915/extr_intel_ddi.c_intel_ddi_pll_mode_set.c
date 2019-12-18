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
typedef  int uint32_t ;
struct drm_encoder {int dummy; } ;
struct intel_encoder {int type; struct drm_encoder base; } ;
struct intel_dp {int link_bw; } ;
struct intel_ddi_plls {scalar_t__ wrpll1_refcount; scalar_t__ wrpll2_refcount; scalar_t__ spll_refcount; } ;
struct intel_crtc {int pipe; int /*<<< orphan*/  ddi_pll_sel; } ;
struct drm_i915_private {struct intel_ddi_plls ddi_plls; } ;
struct drm_crtc {TYPE_1__* dev; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_2__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
#define  DP_LINK_BW_1_62 130 
#define  DP_LINK_BW_2_7 129 
#define  DP_LINK_BW_5_4 128 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int I915_READ (int) ; 
 int /*<<< orphan*/  I915_WRITE (int,int) ; 
 int INTEL_OUTPUT_ANALOG ; 
 int INTEL_OUTPUT_DISPLAYPORT ; 
 int INTEL_OUTPUT_EDP ; 
 int INTEL_OUTPUT_HDMI ; 
 int /*<<< orphan*/  PORT_CLK_SEL_LCPLL_1350 ; 
 int /*<<< orphan*/  PORT_CLK_SEL_LCPLL_2700 ; 
 int /*<<< orphan*/  PORT_CLK_SEL_LCPLL_810 ; 
 int /*<<< orphan*/  PORT_CLK_SEL_SPLL ; 
 int /*<<< orphan*/  PORT_CLK_SEL_WRPLL1 ; 
 int /*<<< orphan*/  PORT_CLK_SEL_WRPLL2 ; 
 int SPLL_CTL ; 
 int SPLL_PLL_ENABLE ; 
 int SPLL_PLL_FREQ_1350MHz ; 
 int SPLL_PLL_SSC ; 
 int /*<<< orphan*/  WARN (int,char*,...) ; 
 int WRPLL_CTL1 ; 
 int WRPLL_CTL2 ; 
 int WRPLL_DIVIDER_FEEDBACK (int) ; 
 int WRPLL_DIVIDER_POST (int) ; 
 int WRPLL_DIVIDER_REFERENCE (int) ; 
 int WRPLL_PLL_ENABLE ; 
 int WRPLL_PLL_SELECT_LCPLL_2700 ; 
 struct intel_dp* enc_to_intel_dp (struct drm_encoder*) ; 
 int /*<<< orphan*/  intel_ddi_calculate_wrpll (int,int*,int*,int*) ; 
 struct intel_encoder* intel_ddi_get_crtc_encoder (struct drm_crtc*) ; 
 int /*<<< orphan*/  intel_ddi_put_crtc_pll (struct drm_crtc*) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool intel_ddi_pll_mode_set(struct drm_crtc *crtc, int clock)
{
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	struct intel_encoder *intel_encoder = intel_ddi_get_crtc_encoder(crtc);
	struct drm_encoder *encoder = &intel_encoder->base;
	struct drm_i915_private *dev_priv = crtc->dev->dev_private;
	struct intel_ddi_plls *plls = &dev_priv->ddi_plls;
	int type = intel_encoder->type;
	enum pipe pipe = intel_crtc->pipe;
	uint32_t reg, val;

	/* TODO: reuse PLLs when possible (compare values) */

	intel_ddi_put_crtc_pll(crtc);

	if (type == INTEL_OUTPUT_DISPLAYPORT || type == INTEL_OUTPUT_EDP) {
		struct intel_dp *intel_dp = enc_to_intel_dp(encoder);

		switch (intel_dp->link_bw) {
		case DP_LINK_BW_1_62:
			intel_crtc->ddi_pll_sel = PORT_CLK_SEL_LCPLL_810;
			break;
		case DP_LINK_BW_2_7:
			intel_crtc->ddi_pll_sel = PORT_CLK_SEL_LCPLL_1350;
			break;
		case DP_LINK_BW_5_4:
			intel_crtc->ddi_pll_sel = PORT_CLK_SEL_LCPLL_2700;
			break;
		default:
			DRM_ERROR("Link bandwidth %d unsupported\n",
				  intel_dp->link_bw);
			return false;
		}

		/* We don't need to turn any PLL on because we'll use LCPLL. */
		return true;

	} else if (type == INTEL_OUTPUT_HDMI) {
		int p, n2, r2;

		if (plls->wrpll1_refcount == 0) {
			DRM_DEBUG_KMS("Using WRPLL 1 on pipe %c\n",
				      pipe_name(pipe));
			plls->wrpll1_refcount++;
			reg = WRPLL_CTL1;
			intel_crtc->ddi_pll_sel = PORT_CLK_SEL_WRPLL1;
		} else if (plls->wrpll2_refcount == 0) {
			DRM_DEBUG_KMS("Using WRPLL 2 on pipe %c\n",
				      pipe_name(pipe));
			plls->wrpll2_refcount++;
			reg = WRPLL_CTL2;
			intel_crtc->ddi_pll_sel = PORT_CLK_SEL_WRPLL2;
		} else {
			DRM_ERROR("No WRPLLs available!\n");
			return false;
		}

		WARN(I915_READ(reg) & WRPLL_PLL_ENABLE,
		     "WRPLL already enabled\n");

		intel_ddi_calculate_wrpll(clock, &p, &n2, &r2);

		val = WRPLL_PLL_ENABLE | WRPLL_PLL_SELECT_LCPLL_2700 |
		      WRPLL_DIVIDER_REFERENCE(r2) | WRPLL_DIVIDER_FEEDBACK(n2) |
		      WRPLL_DIVIDER_POST(p);

	} else if (type == INTEL_OUTPUT_ANALOG) {
		if (plls->spll_refcount == 0) {
			DRM_DEBUG_KMS("Using SPLL on pipe %c\n",
				      pipe_name(pipe));
			plls->spll_refcount++;
			reg = SPLL_CTL;
			intel_crtc->ddi_pll_sel = PORT_CLK_SEL_SPLL;
		}

		WARN(I915_READ(reg) & SPLL_PLL_ENABLE,
		     "SPLL already enabled\n");

		val = SPLL_PLL_ENABLE | SPLL_PLL_FREQ_1350MHz | SPLL_PLL_SSC;

	} else {
		WARN(1, "Invalid DDI encoder type %d\n", type);
		return false;
	}

	I915_WRITE(reg, val);
	udelay(20);

	return true;
}