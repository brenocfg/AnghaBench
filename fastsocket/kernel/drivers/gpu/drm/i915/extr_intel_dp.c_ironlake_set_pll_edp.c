#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_A ; 
 int /*<<< orphan*/  DP_PLL_FREQ_160MHZ ; 
 int /*<<< orphan*/  DP_PLL_FREQ_270MHZ ; 
 int /*<<< orphan*/  DP_PLL_FREQ_MASK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ironlake_set_pll_edp(struct drm_crtc *crtc, int clock)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 dpa_ctl;

	DRM_DEBUG_KMS("eDP PLL enable for clock %d\n", clock);
	dpa_ctl = I915_READ(DP_A);
	dpa_ctl &= ~DP_PLL_FREQ_MASK;

	if (clock < 200000) {
		/* For a long time we've carried around a ILK-DevA w/a for the
		 * 160MHz clock. If we're really unlucky, it's still required.
		 */
		DRM_DEBUG_KMS("160MHz cpu eDP clock, might need ilk devA w/a\n");
		dpa_ctl |= DP_PLL_FREQ_160MHZ;
	} else {
		dpa_ctl |= DP_PLL_FREQ_270MHZ;
	}

	I915_WRITE(DP_A, dpa_ctl);

	POSTING_READ(DP_A);
	udelay(500);
}