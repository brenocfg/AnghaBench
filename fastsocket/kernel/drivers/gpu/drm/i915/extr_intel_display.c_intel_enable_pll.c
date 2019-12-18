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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int /*<<< orphan*/  dev; TYPE_1__* info; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DPLL (int) ; 
 int /*<<< orphan*/  DPLL_VCO_ENABLE ; 
 int /*<<< orphan*/  I915_READ (int) ; 
 int /*<<< orphan*/  I915_WRITE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_I830 (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_MOBILE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_VALLEYVIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POSTING_READ (int) ; 
 int /*<<< orphan*/  assert_panel_unlocked (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void intel_enable_pll(struct drm_i915_private *dev_priv, enum pipe pipe)
{
	int reg;
	u32 val;

	/* No really, not for ILK+ */
	BUG_ON(!IS_VALLEYVIEW(dev_priv->dev) && dev_priv->info->gen >= 5);

	/* PLL is protected by panel, make sure we can write it */
	if (IS_MOBILE(dev_priv->dev) && !IS_I830(dev_priv->dev))
		assert_panel_unlocked(dev_priv, pipe);

	reg = DPLL(pipe);
	val = I915_READ(reg);
	val |= DPLL_VCO_ENABLE;

	/* We do this three times for luck */
	I915_WRITE(reg, val);
	POSTING_READ(reg);
	udelay(150); /* wait for warmup */
	I915_WRITE(reg, val);
	POSTING_READ(reg);
	udelay(150); /* wait for warmup */
	I915_WRITE(reg, val);
	POSTING_READ(reg);
	udelay(150); /* wait for warmup */
}