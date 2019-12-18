#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  saveFBC_CONTROL; int /*<<< orphan*/  saveFBC_CONTROL2; int /*<<< orphan*/  saveFBC_LL_BASE; int /*<<< orphan*/  saveFBC_CFB_BASE; int /*<<< orphan*/  saveDPFC_CB_BASE; int /*<<< orphan*/  savePP_CONTROL; int /*<<< orphan*/  savePP_DIVISOR; int /*<<< orphan*/  savePP_OFF_DELAYS; int /*<<< orphan*/  savePP_ON_DELAYS; int /*<<< orphan*/  saveBLC_HIST_CTL; int /*<<< orphan*/  saveBLC_PWM_CTL; int /*<<< orphan*/  savePFIT_PGM_RATIOS; int /*<<< orphan*/  saveMCHBAR_RENDER_STANDBY; int /*<<< orphan*/  saveBLC_CPU_PWM_CTL; int /*<<< orphan*/  saveBLC_CPU_PWM_CTL2; int /*<<< orphan*/  saveBLC_PWM_CTL2; int /*<<< orphan*/  savePFIT_CONTROL; int /*<<< orphan*/  saveLVDS; int /*<<< orphan*/  saveDSPARB; } ;
struct drm_i915_private {TYPE_1__ regfile; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_4__ {int gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLC_HIST_CTL ; 
 int /*<<< orphan*/  BLC_PWM_CPU_CTL ; 
 int /*<<< orphan*/  BLC_PWM_CPU_CTL2 ; 
 int /*<<< orphan*/  BLC_PWM_CTL ; 
 int /*<<< orphan*/  BLC_PWM_CTL2 ; 
 int /*<<< orphan*/  BLC_PWM_PCH_CTL1 ; 
 int /*<<< orphan*/  BLC_PWM_PCH_CTL2 ; 
 int /*<<< orphan*/  DPFC_CB_BASE ; 
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DSPARB ; 
 int /*<<< orphan*/  FBC_CFB_BASE ; 
 int /*<<< orphan*/  FBC_CONTROL ; 
 int /*<<< orphan*/  FBC_CONTROL2 ; 
 int /*<<< orphan*/  FBC_LL_BASE ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_device*) ; 
 scalar_t__ I915_HAS_FBC (struct drm_device*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILK_DPFC_CB_BASE ; 
 TYPE_2__* INTEL_INFO (struct drm_device*) ; 
 int /*<<< orphan*/  IS_845G (struct drm_device*) ; 
 scalar_t__ IS_GM45 (struct drm_device*) ; 
 int /*<<< orphan*/  IS_I830 (struct drm_device*) ; 
 scalar_t__ IS_MOBILE (struct drm_device*) ; 
 int /*<<< orphan*/  LVDS ; 
 int /*<<< orphan*/  PCH_LVDS ; 
 int /*<<< orphan*/  PCH_PP_CONTROL ; 
 int /*<<< orphan*/  PCH_PP_DIVISOR ; 
 int /*<<< orphan*/  PCH_PP_OFF_DELAYS ; 
 int /*<<< orphan*/  PCH_PP_ON_DELAYS ; 
 int /*<<< orphan*/  PFIT_CONTROL ; 
 int /*<<< orphan*/  PFIT_PGM_RATIOS ; 
 int /*<<< orphan*/  PP_CONTROL ; 
 int /*<<< orphan*/  PP_DIVISOR ; 
 int /*<<< orphan*/  PP_OFF_DELAYS ; 
 int /*<<< orphan*/  PP_ON_DELAYS ; 
 int /*<<< orphan*/  RSTDBYCTL ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_redisable_vga (struct drm_device*) ; 
 int /*<<< orphan*/  i915_restore_display_reg (struct drm_device*) ; 
 int /*<<< orphan*/  i915_restore_vga (struct drm_device*) ; 
 int /*<<< orphan*/  intel_disable_fbc (struct drm_device*) ; 

__attribute__((used)) static void i915_restore_display(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	/* Display arbitration */
	if (INTEL_INFO(dev)->gen <= 4)
		I915_WRITE(DSPARB, dev_priv->regfile.saveDSPARB);

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		i915_restore_display_reg(dev);

	/* LVDS state */
	if (INTEL_INFO(dev)->gen >= 4 && !HAS_PCH_SPLIT(dev))
		I915_WRITE(BLC_PWM_CTL2, dev_priv->regfile.saveBLC_PWM_CTL2);

	if (HAS_PCH_SPLIT(dev)) {
		I915_WRITE(PCH_LVDS, dev_priv->regfile.saveLVDS);
	} else if (IS_MOBILE(dev) && !IS_I830(dev))
		I915_WRITE(LVDS, dev_priv->regfile.saveLVDS);

	if (!IS_I830(dev) && !IS_845G(dev) && !HAS_PCH_SPLIT(dev))
		I915_WRITE(PFIT_CONTROL, dev_priv->regfile.savePFIT_CONTROL);

	if (HAS_PCH_SPLIT(dev)) {
		I915_WRITE(BLC_PWM_PCH_CTL1, dev_priv->regfile.saveBLC_PWM_CTL);
		I915_WRITE(BLC_PWM_PCH_CTL2, dev_priv->regfile.saveBLC_PWM_CTL2);
		/* NOTE: BLC_PWM_CPU_CTL must be written after BLC_PWM_CPU_CTL2;
		 * otherwise we get blank eDP screen after S3 on some machines
		 */
		I915_WRITE(BLC_PWM_CPU_CTL2, dev_priv->regfile.saveBLC_CPU_PWM_CTL2);
		I915_WRITE(BLC_PWM_CPU_CTL, dev_priv->regfile.saveBLC_CPU_PWM_CTL);
		I915_WRITE(PCH_PP_ON_DELAYS, dev_priv->regfile.savePP_ON_DELAYS);
		I915_WRITE(PCH_PP_OFF_DELAYS, dev_priv->regfile.savePP_OFF_DELAYS);
		I915_WRITE(PCH_PP_DIVISOR, dev_priv->regfile.savePP_DIVISOR);
		I915_WRITE(PCH_PP_CONTROL, dev_priv->regfile.savePP_CONTROL);
		I915_WRITE(RSTDBYCTL,
			   dev_priv->regfile.saveMCHBAR_RENDER_STANDBY);
	} else {
		I915_WRITE(PFIT_PGM_RATIOS, dev_priv->regfile.savePFIT_PGM_RATIOS);
		I915_WRITE(BLC_PWM_CTL, dev_priv->regfile.saveBLC_PWM_CTL);
		I915_WRITE(BLC_HIST_CTL, dev_priv->regfile.saveBLC_HIST_CTL);
		I915_WRITE(PP_ON_DELAYS, dev_priv->regfile.savePP_ON_DELAYS);
		I915_WRITE(PP_OFF_DELAYS, dev_priv->regfile.savePP_OFF_DELAYS);
		I915_WRITE(PP_DIVISOR, dev_priv->regfile.savePP_DIVISOR);
		I915_WRITE(PP_CONTROL, dev_priv->regfile.savePP_CONTROL);
	}

	/* only restore FBC info on the platform that supports FBC*/
	intel_disable_fbc(dev);
	if (I915_HAS_FBC(dev)) {
		if (HAS_PCH_SPLIT(dev)) {
			I915_WRITE(ILK_DPFC_CB_BASE, dev_priv->regfile.saveDPFC_CB_BASE);
		} else if (IS_GM45(dev)) {
			I915_WRITE(DPFC_CB_BASE, dev_priv->regfile.saveDPFC_CB_BASE);
		} else {
			I915_WRITE(FBC_CFB_BASE, dev_priv->regfile.saveFBC_CFB_BASE);
			I915_WRITE(FBC_LL_BASE, dev_priv->regfile.saveFBC_LL_BASE);
			I915_WRITE(FBC_CONTROL2, dev_priv->regfile.saveFBC_CONTROL2);
			I915_WRITE(FBC_CONTROL, dev_priv->regfile.saveFBC_CONTROL);
		}
	}

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		i915_restore_vga(dev);
	else
		i915_redisable_vga(dev);
}