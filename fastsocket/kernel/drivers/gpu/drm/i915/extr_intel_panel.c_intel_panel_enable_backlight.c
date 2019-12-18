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
struct drm_i915_private {scalar_t__ backlight_level; int num_pipe; int backlight_enabled; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 int BLC_PWM_CPU_CTL2 ; 
 int BLC_PWM_CTL2 ; 
 int BLC_PWM_PCH_CTL1 ; 
 int BLM_PCH_OVERRIDE_ENABLE ; 
 int BLM_PCH_PWM_ENABLE ; 
 int BLM_PIPE (int) ; 
 int BLM_PIPE_SELECT ; 
 int BLM_PIPE_SELECT_IVB ; 
 int BLM_PWM_ENABLE ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_device*) ; 
 int I915_READ (int) ; 
 int /*<<< orphan*/  I915_WRITE (int,int) ; 
 TYPE_1__* INTEL_INFO (struct drm_device*) ; 
 int /*<<< orphan*/  POSTING_READ (int) ; 
 int /*<<< orphan*/  intel_panel_actually_set_backlight (struct drm_device*,scalar_t__) ; 
 scalar_t__ intel_panel_get_max_backlight (struct drm_device*) ; 

void intel_panel_enable_backlight(struct drm_device *dev,
				  enum pipe pipe)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (dev_priv->backlight_level == 0)
		dev_priv->backlight_level = intel_panel_get_max_backlight(dev);

	if (INTEL_INFO(dev)->gen >= 4) {
		uint32_t reg, tmp;

		reg = HAS_PCH_SPLIT(dev) ? BLC_PWM_CPU_CTL2 : BLC_PWM_CTL2;


		tmp = I915_READ(reg);

		/* Note that this can also get called through dpms changes. And
		 * we don't track the backlight dpms state, hence check whether
		 * we have to do anything first. */
		if (tmp & BLM_PWM_ENABLE)
			goto set_level;

		if (dev_priv->num_pipe == 3)
			tmp &= ~BLM_PIPE_SELECT_IVB;
		else
			tmp &= ~BLM_PIPE_SELECT;

		tmp |= BLM_PIPE(pipe);
		tmp &= ~BLM_PWM_ENABLE;

		I915_WRITE(reg, tmp);
		POSTING_READ(reg);
		I915_WRITE(reg, tmp | BLM_PWM_ENABLE);

		if (HAS_PCH_SPLIT(dev)) {
			tmp = I915_READ(BLC_PWM_PCH_CTL1);
			tmp |= BLM_PCH_PWM_ENABLE;
			tmp &= ~BLM_PCH_OVERRIDE_ENABLE;
			I915_WRITE(BLC_PWM_PCH_CTL1, tmp);
		}
	}

set_level:
	/* Call below after setting BLC_PWM_CPU_CTL2 and BLC_PWM_PCH_CTL1.
	 * BLC_PWM_CPU_CTL may be cleared to zero automatically when these
	 * registers are set.
	 */
	dev_priv->backlight_enabled = true;
	intel_panel_actually_set_backlight(dev, dev_priv->backlight_level);
}