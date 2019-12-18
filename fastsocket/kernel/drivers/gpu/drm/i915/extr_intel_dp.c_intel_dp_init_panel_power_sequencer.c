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
typedef  int u32 ;
struct intel_dp {void* backlight_off_delay; void* backlight_on_delay; void* panel_power_cycle_delay; void* panel_power_down_delay; void* panel_power_up_delay; } ;
struct edp_power_seq {int t1_t3; int t8; int t9; int t10; int t11_t12; } ;
struct TYPE_2__ {struct edp_power_seq pps; } ;
struct drm_i915_private {TYPE_1__ edp; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int,...) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int PANEL_LIGHT_OFF_DELAY_MASK ; 
 int PANEL_LIGHT_OFF_DELAY_SHIFT ; 
 int PANEL_LIGHT_ON_DELAY_MASK ; 
 int PANEL_LIGHT_ON_DELAY_SHIFT ; 
 int PANEL_POWER_CYCLE_DELAY_MASK ; 
 int PANEL_POWER_CYCLE_DELAY_SHIFT ; 
 int PANEL_POWER_DOWN_DELAY_MASK ; 
 int PANEL_POWER_DOWN_DELAY_SHIFT ; 
 int PANEL_POWER_UP_DELAY_MASK ; 
 int PANEL_POWER_UP_DELAY_SHIFT ; 
 int /*<<< orphan*/  PCH_PP_CONTROL ; 
 int /*<<< orphan*/  PCH_PP_DIVISOR ; 
 int /*<<< orphan*/  PCH_PP_OFF_DELAYS ; 
 int /*<<< orphan*/  PCH_PP_ON_DELAYS ; 
 int /*<<< orphan*/  assign_final (int /*<<< orphan*/ ) ; 
 void* get_delay (int /*<<< orphan*/ ) ; 
 int ironlake_get_pp_control (struct drm_i915_private*) ; 
 int /*<<< orphan*/  t10 ; 
 int /*<<< orphan*/  t11_t12 ; 
 int /*<<< orphan*/  t1_t3 ; 
 int /*<<< orphan*/  t8 ; 
 int /*<<< orphan*/  t9 ; 

__attribute__((used)) static void
intel_dp_init_panel_power_sequencer(struct drm_device *dev,
				    struct intel_dp *intel_dp,
				    struct edp_power_seq *out)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct edp_power_seq cur, vbt, spec, final;
	u32 pp_on, pp_off, pp_div, pp;

	/* Workaround: Need to write PP_CONTROL with the unlock key as
	 * the very first thing. */
	pp = ironlake_get_pp_control(dev_priv);
	I915_WRITE(PCH_PP_CONTROL, pp);

	pp_on = I915_READ(PCH_PP_ON_DELAYS);
	pp_off = I915_READ(PCH_PP_OFF_DELAYS);
	pp_div = I915_READ(PCH_PP_DIVISOR);

	/* Pull timing values out of registers */
	cur.t1_t3 = (pp_on & PANEL_POWER_UP_DELAY_MASK) >>
		PANEL_POWER_UP_DELAY_SHIFT;

	cur.t8 = (pp_on & PANEL_LIGHT_ON_DELAY_MASK) >>
		PANEL_LIGHT_ON_DELAY_SHIFT;

	cur.t9 = (pp_off & PANEL_LIGHT_OFF_DELAY_MASK) >>
		PANEL_LIGHT_OFF_DELAY_SHIFT;

	cur.t10 = (pp_off & PANEL_POWER_DOWN_DELAY_MASK) >>
		PANEL_POWER_DOWN_DELAY_SHIFT;

	cur.t11_t12 = ((pp_div & PANEL_POWER_CYCLE_DELAY_MASK) >>
		       PANEL_POWER_CYCLE_DELAY_SHIFT) * 1000;

	DRM_DEBUG_KMS("cur t1_t3 %d t8 %d t9 %d t10 %d t11_t12 %d\n",
		      cur.t1_t3, cur.t8, cur.t9, cur.t10, cur.t11_t12);

	vbt = dev_priv->edp.pps;

	/* Upper limits from eDP 1.3 spec. Note that we use the clunky units of
	 * our hw here, which are all in 100usec. */
	spec.t1_t3 = 210 * 10;
	spec.t8 = 50 * 10; /* no limit for t8, use t7 instead */
	spec.t9 = 50 * 10; /* no limit for t9, make it symmetric with t8 */
	spec.t10 = 500 * 10;
	/* This one is special and actually in units of 100ms, but zero
	 * based in the hw (so we need to add 100 ms). But the sw vbt
	 * table multiplies it with 1000 to make it in units of 100usec,
	 * too. */
	spec.t11_t12 = (510 + 100) * 10;

	DRM_DEBUG_KMS("vbt t1_t3 %d t8 %d t9 %d t10 %d t11_t12 %d\n",
		      vbt.t1_t3, vbt.t8, vbt.t9, vbt.t10, vbt.t11_t12);

	/* Use the max of the register settings and vbt. If both are
	 * unset, fall back to the spec limits. */
#define assign_final(field)	final.field = (max(cur.field, vbt.field) == 0 ? \
				       spec.field : \
				       max(cur.field, vbt.field))
	assign_final(t1_t3);
	assign_final(t8);
	assign_final(t9);
	assign_final(t10);
	assign_final(t11_t12);
#undef assign_final

#define get_delay(field)	(DIV_ROUND_UP(final.field, 10))
	intel_dp->panel_power_up_delay = get_delay(t1_t3);
	intel_dp->backlight_on_delay = get_delay(t8);
	intel_dp->backlight_off_delay = get_delay(t9);
	intel_dp->panel_power_down_delay = get_delay(t10);
	intel_dp->panel_power_cycle_delay = get_delay(t11_t12);
#undef get_delay

	DRM_DEBUG_KMS("panel power up delay %d, power down delay %d, power cycle delay %d\n",
		      intel_dp->panel_power_up_delay, intel_dp->panel_power_down_delay,
		      intel_dp->panel_power_cycle_delay);

	DRM_DEBUG_KMS("backlight on delay %d, off delay %d\n",
		      intel_dp->backlight_on_delay, intel_dp->backlight_off_delay);

	if (out)
		*out = final;
}