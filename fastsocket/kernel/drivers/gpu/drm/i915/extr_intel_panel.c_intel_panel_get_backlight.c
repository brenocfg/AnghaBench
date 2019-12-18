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
typedef  int u8 ;
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int /*<<< orphan*/  pdev; struct drm_i915_private* dev_private; } ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 int BACKLIGHT_DUTY_CYCLE_MASK ; 
 int /*<<< orphan*/  BLC_PWM_CPU_CTL ; 
 int /*<<< orphan*/  BLC_PWM_CTL ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_device*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 TYPE_1__* INTEL_INFO (struct drm_device*) ; 
 int /*<<< orphan*/  PCI_LBPC ; 
 int intel_panel_compute_brightness (struct drm_device*,int) ; 
 scalar_t__ is_backlight_combination_mode (struct drm_device*) ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static u32 intel_panel_get_backlight(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 val;

	if (HAS_PCH_SPLIT(dev)) {
		val = I915_READ(BLC_PWM_CPU_CTL) & BACKLIGHT_DUTY_CYCLE_MASK;
	} else {
		val = I915_READ(BLC_PWM_CTL) & BACKLIGHT_DUTY_CYCLE_MASK;
		if (INTEL_INFO(dev)->gen < 4)
			val >>= 1;

		if (is_backlight_combination_mode(dev)) {
			u8 lbpc;

			pci_read_config_byte(dev->pdev, PCI_LBPC, &lbpc);
			val *= lbpc;
		}
	}

	val = intel_panel_compute_brightness(dev, val);
	DRM_DEBUG_DRIVER("get backlight PWM = %d\n", val);
	return val;
}