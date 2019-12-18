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
struct intel_ddi_plls {scalar_t__ spll_refcount; scalar_t__ wrpll1_refcount; scalar_t__ wrpll2_refcount; } ;
struct intel_crtc {int ddi_pll_sel; } ;
struct drm_i915_private {struct intel_ddi_plls ddi_plls; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct TYPE_2__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int PORT_CLK_SEL_NONE ; 
#define  PORT_CLK_SEL_SPLL 130 
#define  PORT_CLK_SEL_WRPLL1 129 
#define  PORT_CLK_SEL_WRPLL2 128 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPLL_CTL ; 
 int SPLL_PLL_ENABLE ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WRPLL_CTL1 ; 
 int /*<<< orphan*/  WRPLL_CTL2 ; 
 int WRPLL_PLL_ENABLE ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

void intel_ddi_put_crtc_pll(struct drm_crtc *crtc)
{
	struct drm_i915_private *dev_priv = crtc->dev->dev_private;
	struct intel_ddi_plls *plls = &dev_priv->ddi_plls;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	uint32_t val;

	switch (intel_crtc->ddi_pll_sel) {
	case PORT_CLK_SEL_SPLL:
		plls->spll_refcount--;
		if (plls->spll_refcount == 0) {
			DRM_DEBUG_KMS("Disabling SPLL\n");
			val = I915_READ(SPLL_CTL);
			WARN_ON(!(val & SPLL_PLL_ENABLE));
			I915_WRITE(SPLL_CTL, val & ~SPLL_PLL_ENABLE);
			POSTING_READ(SPLL_CTL);
		}
		break;
	case PORT_CLK_SEL_WRPLL1:
		plls->wrpll1_refcount--;
		if (plls->wrpll1_refcount == 0) {
			DRM_DEBUG_KMS("Disabling WRPLL 1\n");
			val = I915_READ(WRPLL_CTL1);
			WARN_ON(!(val & WRPLL_PLL_ENABLE));
			I915_WRITE(WRPLL_CTL1, val & ~WRPLL_PLL_ENABLE);
			POSTING_READ(WRPLL_CTL1);
		}
		break;
	case PORT_CLK_SEL_WRPLL2:
		plls->wrpll2_refcount--;
		if (plls->wrpll2_refcount == 0) {
			DRM_DEBUG_KMS("Disabling WRPLL 2\n");
			val = I915_READ(WRPLL_CTL2);
			WARN_ON(!(val & WRPLL_PLL_ENABLE));
			I915_WRITE(WRPLL_CTL2, val & ~WRPLL_PLL_ENABLE);
			POSTING_READ(WRPLL_CTL2);
		}
		break;
	}

	WARN(plls->spll_refcount < 0, "Invalid SPLL refcount\n");
	WARN(plls->wrpll1_refcount < 0, "Invalid WRPLL1 refcount\n");
	WARN(plls->wrpll2_refcount < 0, "Invalid WRPLL2 refcount\n");

	intel_crtc->ddi_pll_sel = PORT_CLK_SEL_NONE;
}