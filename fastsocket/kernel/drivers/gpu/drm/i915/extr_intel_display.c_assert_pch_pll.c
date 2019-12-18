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
typedef  int u32 ;
struct intel_pch_pll {int pll_reg; } ;
struct intel_crtc {int pipe; } ;
struct drm_i915_private {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DPLL_VCO_ENABLE ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 scalar_t__ HAS_PCH_CPT (int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_PCH_LPT (int /*<<< orphan*/ ) ; 
 int I915_READ (int) ; 
 int PCH_DPLL_SEL ; 
 int /*<<< orphan*/  WARN (int,char*,int,...) ; 
 int _PCH_DPLL_B ; 
 int state_string (int) ; 

__attribute__((used)) static void assert_pch_pll(struct drm_i915_private *dev_priv,
			   struct intel_pch_pll *pll,
			   struct intel_crtc *crtc,
			   bool state)
{
	u32 val;
	bool cur_state;

	if (HAS_PCH_LPT(dev_priv->dev)) {
		DRM_DEBUG_DRIVER("LPT detected: skipping PCH PLL test\n");
		return;
	}

	if (WARN (!pll,
		  "asserting PCH PLL %s with no PLL\n", state_string(state)))
		return;

	val = I915_READ(pll->pll_reg);
	cur_state = !!(val & DPLL_VCO_ENABLE);
	WARN(cur_state != state,
	     "PCH PLL state for reg %x assertion failure (expected %s, current %s), val=%08x\n",
	     pll->pll_reg, state_string(state), state_string(cur_state), val);

	/* Make sure the selected PLL is correctly attached to the transcoder */
	if (crtc && HAS_PCH_CPT(dev_priv->dev)) {
		u32 pch_dpll;

		pch_dpll = I915_READ(PCH_DPLL_SEL);
		cur_state = pll->pll_reg == _PCH_DPLL_B;
		if (!WARN(((pch_dpll >> (4 * crtc->pipe)) & 1) != cur_state,
			  "PLL[%d] not attached to this transcoder %d: %08x\n",
			  cur_state, crtc->pipe, pch_dpll)) {
			cur_state = !!(val >> (4*crtc->pipe + 3));
			WARN(cur_state != state,
			     "PLL[%d] not %s on this transcoder %d: %08x\n",
			     pll->pll_reg == _PCH_DPLL_B,
			     state_string(state),
			     crtc->pipe,
			     val);
		}
	}
}