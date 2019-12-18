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
struct drm_i915_private {int quirks; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int DPLL (int) ; 
 int /*<<< orphan*/  DPLL_VCO_ENABLE ; 
 int /*<<< orphan*/  I915_READ (int) ; 
 int /*<<< orphan*/  I915_WRITE (int,int /*<<< orphan*/ ) ; 
 int PIPE_A ; 
 int /*<<< orphan*/  POSTING_READ (int) ; 
 int QUIRK_PIPEA_FORCE ; 
 int /*<<< orphan*/  assert_pipe_disabled (struct drm_i915_private*,int) ; 

__attribute__((used)) static void intel_disable_pll(struct drm_i915_private *dev_priv, enum pipe pipe)
{
	int reg;
	u32 val;

	/* Don't disable pipe A or pipe A PLLs if needed */
	if (pipe == PIPE_A && (dev_priv->quirks & QUIRK_PIPEA_FORCE))
		return;

	/* Make sure the pipe isn't still relying on us */
	assert_pipe_disabled(dev_priv, pipe);

	reg = DPLL(pipe);
	val = I915_READ(reg);
	val &= ~DPLL_VCO_ENABLE;
	I915_WRITE(reg, val);
	POSTING_READ(reg);
}