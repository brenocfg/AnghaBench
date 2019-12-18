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
struct drm_device {scalar_t__ dev_private; } ;
typedef  int /*<<< orphan*/  drm_i915_private_t ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCH_PORT_HOTPLUG ; 
 int PORTB_HOTPLUG_ENABLE ; 
 int PORTB_PULSE_DURATION_2ms ; 
 int PORTB_PULSE_DURATION_MASK ; 
 int PORTC_HOTPLUG_ENABLE ; 
 int PORTC_PULSE_DURATION_2ms ; 
 int PORTC_PULSE_DURATION_MASK ; 
 int PORTD_HOTPLUG_ENABLE ; 
 int PORTD_PULSE_DURATION_2ms ; 
 int PORTD_PULSE_DURATION_MASK ; 

__attribute__((used)) static void ibx_enable_hotplug(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = (drm_i915_private_t *) dev->dev_private;
	u32	hotplug;

	hotplug = I915_READ(PCH_PORT_HOTPLUG);
	hotplug &= ~(PORTD_PULSE_DURATION_MASK|PORTC_PULSE_DURATION_MASK|PORTB_PULSE_DURATION_MASK);
	hotplug |= PORTD_HOTPLUG_ENABLE | PORTD_PULSE_DURATION_2ms;
	hotplug |= PORTC_HOTPLUG_ENABLE | PORTC_PULSE_DURATION_2ms;
	hotplug |= PORTB_HOTPLUG_ENABLE | PORTB_PULSE_DURATION_2ms;
	I915_WRITE(PCH_PORT_HOTPLUG, hotplug);
}