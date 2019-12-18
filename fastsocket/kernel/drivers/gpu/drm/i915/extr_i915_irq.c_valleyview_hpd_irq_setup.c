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
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_2__ {int hotplug_supported_mask; } ;
typedef  TYPE_1__ drm_i915_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_HOTPLUG_INT_EN ; 
 int CRT_HOTPLUG_INT_STATUS ; 
 int /*<<< orphan*/  CRT_HOTPLUG_VOLTAGE_COMPARE_50 ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORTB_HOTPLUG_INT_EN ; 
 int PORTB_HOTPLUG_INT_STATUS ; 
 int /*<<< orphan*/  PORTC_HOTPLUG_INT_EN ; 
 int PORTC_HOTPLUG_INT_STATUS ; 
 int /*<<< orphan*/  PORTD_HOTPLUG_INT_EN ; 
 int PORTD_HOTPLUG_INT_STATUS ; 
 int /*<<< orphan*/  PORT_HOTPLUG_EN ; 
 int /*<<< orphan*/  SDVOB_HOTPLUG_INT_EN ; 
 int SDVOB_HOTPLUG_INT_STATUS_I915 ; 
 int /*<<< orphan*/  SDVOC_HOTPLUG_INT_EN ; 
 int SDVOC_HOTPLUG_INT_STATUS_I915 ; 

__attribute__((used)) static void valleyview_hpd_irq_setup(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = (drm_i915_private_t *) dev->dev_private;
	u32 hotplug_en = I915_READ(PORT_HOTPLUG_EN);

	/* Note HDMI and DP share bits */
	if (dev_priv->hotplug_supported_mask & PORTB_HOTPLUG_INT_STATUS)
		hotplug_en |= PORTB_HOTPLUG_INT_EN;
	if (dev_priv->hotplug_supported_mask & PORTC_HOTPLUG_INT_STATUS)
		hotplug_en |= PORTC_HOTPLUG_INT_EN;
	if (dev_priv->hotplug_supported_mask & PORTD_HOTPLUG_INT_STATUS)
		hotplug_en |= PORTD_HOTPLUG_INT_EN;
	if (dev_priv->hotplug_supported_mask & SDVOC_HOTPLUG_INT_STATUS_I915)
		hotplug_en |= SDVOC_HOTPLUG_INT_EN;
	if (dev_priv->hotplug_supported_mask & SDVOB_HOTPLUG_INT_STATUS_I915)
		hotplug_en |= SDVOB_HOTPLUG_INT_EN;
	if (dev_priv->hotplug_supported_mask & CRT_HOTPLUG_INT_STATUS) {
		hotplug_en |= CRT_HOTPLUG_INT_EN;
		hotplug_en |= CRT_HOTPLUG_VOLTAGE_COMPARE_50;
	}

	I915_WRITE(PORT_HOTPLUG_EN, hotplug_en);
}