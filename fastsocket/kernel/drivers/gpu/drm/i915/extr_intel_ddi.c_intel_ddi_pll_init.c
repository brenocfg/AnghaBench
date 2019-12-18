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
typedef  int uint32_t ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int LCPLL_CD_SOURCE_FCLK ; 
 int /*<<< orphan*/  LCPLL_CTL ; 
 int LCPLL_PLL_DISABLE ; 
 int /*<<< orphan*/  intel_ddi_get_cdclk_freq (struct drm_i915_private*) ; 

void intel_ddi_pll_init(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	uint32_t val = I915_READ(LCPLL_CTL);

	/* The LCPLL register should be turned on by the BIOS. For now let's
	 * just check its state and print errors in case something is wrong.
	 * Don't even try to turn it on.
	 */

	DRM_DEBUG_KMS("CDCLK running at %dMHz\n",
		      intel_ddi_get_cdclk_freq(dev_priv));

	if (val & LCPLL_CD_SOURCE_FCLK)
		DRM_ERROR("CDCLK source is not LCPLL\n");

	if (val & LCPLL_PLL_DISABLE)
		DRM_ERROR("LCPLL is disabled\n");
}