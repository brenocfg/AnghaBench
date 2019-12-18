#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_crtc {int pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_3__ {int m1; int n; int m2; int p1; int p2; int dot; } ;
typedef  TYPE_1__ intel_clock_t ;

/* Variables and functions */
 int DISPLAY_RATE_SELECT_FPA1 ; 
 int /*<<< orphan*/  DPLL (int) ; 
 int DPLLB_LVDS_P2_CLOCK_DIV_7 ; 
#define  DPLLB_MODE_DAC_SERIAL 129 
#define  DPLLB_MODE_LVDS 128 
 int DPLL_DAC_SERIAL_P2_CLOCK_DIV_5 ; 
 int DPLL_FPA01_P1_POST_DIV_MASK ; 
 int DPLL_FPA01_P1_POST_DIV_MASK_I830 ; 
 int DPLL_FPA01_P1_POST_DIV_MASK_I830_LVDS ; 
 int DPLL_FPA01_P1_POST_DIV_MASK_PINEVIEW ; 
 int DPLL_FPA01_P1_POST_DIV_SHIFT ; 
 int DPLL_FPA01_P1_POST_DIV_SHIFT_PINEVIEW ; 
 int DPLL_MODE_MASK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int /*<<< orphan*/  FP0 (int) ; 
 int /*<<< orphan*/  FP1 (int) ; 
 int FP_M1_DIV_MASK ; 
 int FP_M1_DIV_SHIFT ; 
 int FP_M2_DIV_MASK ; 
 int FP_M2_DIV_SHIFT ; 
 int FP_M2_PINEVIEW_DIV_MASK ; 
 int FP_N_DIV_MASK ; 
 int FP_N_DIV_SHIFT ; 
 int FP_N_PINEVIEW_DIV_MASK ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_GEN2 (struct drm_device*) ; 
 scalar_t__ IS_PINEVIEW (struct drm_device*) ; 
 int /*<<< orphan*/  LVDS ; 
 int LVDS_PORT_EN ; 
 int PLLB_REF_INPUT_SPREADSPECTRUMIN ; 
 int PLL_P1_DIVIDE_BY_TWO ; 
 int PLL_P2_DIVIDE_BY_4 ; 
 int PLL_REF_INPUT_MASK ; 
 void* ffs (int) ; 
 int /*<<< orphan*/  intel_clock (struct drm_device*,int,TYPE_1__*) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static int intel_crtc_clock_get(struct drm_device *dev, struct drm_crtc *crtc)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe;
	u32 dpll = I915_READ(DPLL(pipe));
	u32 fp;
	intel_clock_t clock;

	if ((dpll & DISPLAY_RATE_SELECT_FPA1) == 0)
		fp = I915_READ(FP0(pipe));
	else
		fp = I915_READ(FP1(pipe));

	clock.m1 = (fp & FP_M1_DIV_MASK) >> FP_M1_DIV_SHIFT;
	if (IS_PINEVIEW(dev)) {
		clock.n = ffs((fp & FP_N_PINEVIEW_DIV_MASK) >> FP_N_DIV_SHIFT) - 1;
		clock.m2 = (fp & FP_M2_PINEVIEW_DIV_MASK) >> FP_M2_DIV_SHIFT;
	} else {
		clock.n = (fp & FP_N_DIV_MASK) >> FP_N_DIV_SHIFT;
		clock.m2 = (fp & FP_M2_DIV_MASK) >> FP_M2_DIV_SHIFT;
	}

	if (!IS_GEN2(dev)) {
		if (IS_PINEVIEW(dev))
			clock.p1 = ffs((dpll & DPLL_FPA01_P1_POST_DIV_MASK_PINEVIEW) >>
				DPLL_FPA01_P1_POST_DIV_SHIFT_PINEVIEW);
		else
			clock.p1 = ffs((dpll & DPLL_FPA01_P1_POST_DIV_MASK) >>
			       DPLL_FPA01_P1_POST_DIV_SHIFT);

		switch (dpll & DPLL_MODE_MASK) {
		case DPLLB_MODE_DAC_SERIAL:
			clock.p2 = dpll & DPLL_DAC_SERIAL_P2_CLOCK_DIV_5 ?
				5 : 10;
			break;
		case DPLLB_MODE_LVDS:
			clock.p2 = dpll & DPLLB_LVDS_P2_CLOCK_DIV_7 ?
				7 : 14;
			break;
		default:
			DRM_DEBUG_KMS("Unknown DPLL mode %08x in programmed "
				  "mode\n", (int)(dpll & DPLL_MODE_MASK));
			return 0;
		}

		/* XXX: Handle the 100Mhz refclk */
		intel_clock(dev, 96000, &clock);
	} else {
		bool is_lvds = (pipe == 1) && (I915_READ(LVDS) & LVDS_PORT_EN);

		if (is_lvds) {
			clock.p1 = ffs((dpll & DPLL_FPA01_P1_POST_DIV_MASK_I830_LVDS) >>
				       DPLL_FPA01_P1_POST_DIV_SHIFT);
			clock.p2 = 14;

			if ((dpll & PLL_REF_INPUT_MASK) ==
			    PLLB_REF_INPUT_SPREADSPECTRUMIN) {
				/* XXX: might not be 66MHz */
				intel_clock(dev, 66000, &clock);
			} else
				intel_clock(dev, 48000, &clock);
		} else {
			if (dpll & PLL_P1_DIVIDE_BY_TWO)
				clock.p1 = 2;
			else {
				clock.p1 = ((dpll & DPLL_FPA01_P1_POST_DIV_MASK_I830) >>
					    DPLL_FPA01_P1_POST_DIV_SHIFT) + 2;
			}
			if (dpll & PLL_P2_DIVIDE_BY_4)
				clock.p2 = 4;
			else
				clock.p2 = 2;

			intel_clock(dev, 48000, &clock);
		}
	}

	/* XXX: It would be nice to validate the clocks, but we can't reuse
	 * i830PllIsValid() because it relies on the xf86_config connector
	 * configuration being accurate, which it isn't necessarily.
	 */

	return clock.dot;
}