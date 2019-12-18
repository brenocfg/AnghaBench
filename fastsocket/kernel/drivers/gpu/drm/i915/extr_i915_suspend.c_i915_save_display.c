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
struct TYPE_3__ {void* saveFBC_CONTROL; void* saveFBC_CONTROL2; void* saveFBC_LL_BASE; void* saveFBC_CFB_BASE; void* saveDPFC_CB_BASE; void* savePP_DIVISOR; void* savePP_OFF_DELAYS; void* savePP_ON_DELAYS; void* savePFIT_CONTROL; void* saveLVDS; void* saveBLC_PWM_CTL2; void* saveBLC_HIST_CTL; void* saveBLC_PWM_CTL; void* savePFIT_PGM_RATIOS; void* savePP_CONTROL; void* saveBLC_CPU_PWM_CTL2; void* saveBLC_CPU_PWM_CTL; void* saveDSPARB; } ;
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
 void* I915_READ (int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_save_display_reg (struct drm_device*) ; 
 int /*<<< orphan*/  i915_save_vga (struct drm_device*) ; 

__attribute__((used)) static void i915_save_display(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	/* Display arbitration control */
	if (INTEL_INFO(dev)->gen <= 4)
		dev_priv->regfile.saveDSPARB = I915_READ(DSPARB);

	/* This is only meaningful in non-KMS mode */
	/* Don't regfile.save them in KMS mode */
	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		i915_save_display_reg(dev);

	/* LVDS state */
	if (HAS_PCH_SPLIT(dev)) {
		dev_priv->regfile.savePP_CONTROL = I915_READ(PCH_PP_CONTROL);
		dev_priv->regfile.saveBLC_PWM_CTL = I915_READ(BLC_PWM_PCH_CTL1);
		dev_priv->regfile.saveBLC_PWM_CTL2 = I915_READ(BLC_PWM_PCH_CTL2);
		dev_priv->regfile.saveBLC_CPU_PWM_CTL = I915_READ(BLC_PWM_CPU_CTL);
		dev_priv->regfile.saveBLC_CPU_PWM_CTL2 = I915_READ(BLC_PWM_CPU_CTL2);
		dev_priv->regfile.saveLVDS = I915_READ(PCH_LVDS);
	} else {
		dev_priv->regfile.savePP_CONTROL = I915_READ(PP_CONTROL);
		dev_priv->regfile.savePFIT_PGM_RATIOS = I915_READ(PFIT_PGM_RATIOS);
		dev_priv->regfile.saveBLC_PWM_CTL = I915_READ(BLC_PWM_CTL);
		dev_priv->regfile.saveBLC_HIST_CTL = I915_READ(BLC_HIST_CTL);
		if (INTEL_INFO(dev)->gen >= 4)
			dev_priv->regfile.saveBLC_PWM_CTL2 = I915_READ(BLC_PWM_CTL2);
		if (IS_MOBILE(dev) && !IS_I830(dev))
			dev_priv->regfile.saveLVDS = I915_READ(LVDS);
	}

	if (!IS_I830(dev) && !IS_845G(dev) && !HAS_PCH_SPLIT(dev))
		dev_priv->regfile.savePFIT_CONTROL = I915_READ(PFIT_CONTROL);

	if (HAS_PCH_SPLIT(dev)) {
		dev_priv->regfile.savePP_ON_DELAYS = I915_READ(PCH_PP_ON_DELAYS);
		dev_priv->regfile.savePP_OFF_DELAYS = I915_READ(PCH_PP_OFF_DELAYS);
		dev_priv->regfile.savePP_DIVISOR = I915_READ(PCH_PP_DIVISOR);
	} else {
		dev_priv->regfile.savePP_ON_DELAYS = I915_READ(PP_ON_DELAYS);
		dev_priv->regfile.savePP_OFF_DELAYS = I915_READ(PP_OFF_DELAYS);
		dev_priv->regfile.savePP_DIVISOR = I915_READ(PP_DIVISOR);
	}

	/* Only regfile.save FBC state on the platform that supports FBC */
	if (I915_HAS_FBC(dev)) {
		if (HAS_PCH_SPLIT(dev)) {
			dev_priv->regfile.saveDPFC_CB_BASE = I915_READ(ILK_DPFC_CB_BASE);
		} else if (IS_GM45(dev)) {
			dev_priv->regfile.saveDPFC_CB_BASE = I915_READ(DPFC_CB_BASE);
		} else {
			dev_priv->regfile.saveFBC_CFB_BASE = I915_READ(FBC_CFB_BASE);
			dev_priv->regfile.saveFBC_LL_BASE = I915_READ(FBC_LL_BASE);
			dev_priv->regfile.saveFBC_CONTROL2 = I915_READ(FBC_CONTROL2);
			dev_priv->regfile.saveFBC_CONTROL = I915_READ(FBC_CONTROL);
		}
	}

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		i915_save_vga(dev);
}