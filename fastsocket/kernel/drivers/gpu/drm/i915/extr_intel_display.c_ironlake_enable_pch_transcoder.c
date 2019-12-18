#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct drm_i915_private {struct drm_device* dev; TYPE_1__* info; struct drm_crtc** pipe_to_crtc_mapping; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_5__ {int /*<<< orphan*/  pch_pll; } ;
struct TYPE_4__ {int gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 scalar_t__ HAS_PCH_CPT (struct drm_device*) ; 
 scalar_t__ HAS_PCH_IBX (struct drm_device*) ; 
 int I915_READ (int) ; 
 int /*<<< orphan*/  I915_WRITE (int,int) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_SDVO ; 
 int PIPECONF (int) ; 
 int PIPECONF_BPC_MASK ; 
 int PIPECONF_INTERLACED_ILK ; 
 int PIPECONF_INTERLACE_MASK ; 
 int TRANSCONF (int) ; 
 int TRANS_CHICKEN2 (int) ; 
 int TRANS_CHICKEN2_TIMING_OVERRIDE ; 
 int TRANS_ENABLE ; 
 int TRANS_INTERLACED ; 
 int TRANS_INTERLACE_MASK ; 
 int TRANS_LEGACY_INTERLACED_ILK ; 
 int TRANS_PROGRESSIVE ; 
 int TRANS_STATE_ENABLE ; 
 int /*<<< orphan*/  assert_fdi_rx_enabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  assert_fdi_tx_enabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  assert_pch_pll_enabled (struct drm_i915_private*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ intel_pipe_has_type (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 TYPE_2__* to_intel_crtc (struct drm_crtc*) ; 
 scalar_t__ wait_for (int,int) ; 

__attribute__((used)) static void ironlake_enable_pch_transcoder(struct drm_i915_private *dev_priv,
					   enum pipe pipe)
{
	struct drm_device *dev = dev_priv->dev;
	struct drm_crtc *crtc = dev_priv->pipe_to_crtc_mapping[pipe];
	uint32_t reg, val, pipeconf_val;

	/* PCH only available on ILK+ */
	BUG_ON(dev_priv->info->gen < 5);

	/* Make sure PCH DPLL is enabled */
	assert_pch_pll_enabled(dev_priv,
			       to_intel_crtc(crtc)->pch_pll,
			       to_intel_crtc(crtc));

	/* FDI must be feeding us bits for PCH ports */
	assert_fdi_tx_enabled(dev_priv, pipe);
	assert_fdi_rx_enabled(dev_priv, pipe);

	if (HAS_PCH_CPT(dev)) {
		/* Workaround: Set the timing override bit before enabling the
		 * pch transcoder. */
		reg = TRANS_CHICKEN2(pipe);
		val = I915_READ(reg);
		val |= TRANS_CHICKEN2_TIMING_OVERRIDE;
		I915_WRITE(reg, val);
	}

	reg = TRANSCONF(pipe);
	val = I915_READ(reg);
	pipeconf_val = I915_READ(PIPECONF(pipe));

	if (HAS_PCH_IBX(dev_priv->dev)) {
		/*
		 * make the BPC in transcoder be consistent with
		 * that in pipeconf reg.
		 */
		val &= ~PIPECONF_BPC_MASK;
		val |= pipeconf_val & PIPECONF_BPC_MASK;
	}

	val &= ~TRANS_INTERLACE_MASK;
	if ((pipeconf_val & PIPECONF_INTERLACE_MASK) == PIPECONF_INTERLACED_ILK)
		if (HAS_PCH_IBX(dev_priv->dev) &&
		    intel_pipe_has_type(crtc, INTEL_OUTPUT_SDVO))
			val |= TRANS_LEGACY_INTERLACED_ILK;
		else
			val |= TRANS_INTERLACED;
	else
		val |= TRANS_PROGRESSIVE;

	I915_WRITE(reg, val | TRANS_ENABLE);
	if (wait_for(I915_READ(reg) & TRANS_STATE_ENABLE, 100))
		DRM_ERROR("failed to enable transcoder %d\n", pipe);
}