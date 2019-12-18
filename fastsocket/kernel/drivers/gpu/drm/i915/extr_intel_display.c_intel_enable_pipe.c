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
struct drm_i915_private {int /*<<< orphan*/  dev; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 scalar_t__ HAS_PCH_LPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAS_PCH_SPLIT (int /*<<< orphan*/ ) ; 
 int I915_READ (int) ; 
 int /*<<< orphan*/  I915_WRITE (int,int) ; 
 int PIPECONF (int) ; 
 int PIPECONF_ENABLE ; 
 int TRANSCODER_A ; 
 int /*<<< orphan*/  assert_fdi_rx_pll_enabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  assert_fdi_tx_pll_enabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  assert_pll_enabled (struct drm_i915_private*,int) ; 
 int intel_pipe_to_cpu_transcoder (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_wait_for_vblank (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void intel_enable_pipe(struct drm_i915_private *dev_priv, enum pipe pipe,
			      bool pch_port)
{
	enum transcoder cpu_transcoder = intel_pipe_to_cpu_transcoder(dev_priv,
								      pipe);
	enum pipe pch_transcoder;
	int reg;
	u32 val;

	if (HAS_PCH_LPT(dev_priv->dev))
		pch_transcoder = TRANSCODER_A;
	else
		pch_transcoder = pipe;

	/*
	 * A pipe without a PLL won't actually be able to drive bits from
	 * a plane.  On ILK+ the pipe PLLs are integrated, so we don't
	 * need the check.
	 */
	if (!HAS_PCH_SPLIT(dev_priv->dev))
		assert_pll_enabled(dev_priv, pipe);
	else {
		if (pch_port) {
			/* if driving the PCH, we need FDI enabled */
			assert_fdi_rx_pll_enabled(dev_priv, pch_transcoder);
			assert_fdi_tx_pll_enabled(dev_priv,
						  (enum pipe) cpu_transcoder);
		}
		/* FIXME: assert CPU port conditions for SNB+ */
	}

	reg = PIPECONF(cpu_transcoder);
	val = I915_READ(reg);
	if (val & PIPECONF_ENABLE)
		return;

	I915_WRITE(reg, val | PIPECONF_ENABLE);
	intel_wait_for_vblank(dev_priv->dev, pipe);
}