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
struct intel_digital_port {int port; } ;
struct drm_i915_private {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ HAS_PCH_IBX (int /*<<< orphan*/ ) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
#define  PORT_B 130 
#define  PORT_C 129 
#define  PORT_D 128 
 int /*<<< orphan*/  SDEISR ; 
 int SDE_PORTB_HOTPLUG ; 
 int SDE_PORTB_HOTPLUG_CPT ; 
 int SDE_PORTC_HOTPLUG ; 
 int SDE_PORTC_HOTPLUG_CPT ; 
 int SDE_PORTD_HOTPLUG ; 
 int SDE_PORTD_HOTPLUG_CPT ; 

bool ibx_digital_port_connected(struct drm_i915_private *dev_priv,
				struct intel_digital_port *port)
{
	u32 bit;

	if (HAS_PCH_IBX(dev_priv->dev)) {
		switch(port->port) {
		case PORT_B:
			bit = SDE_PORTB_HOTPLUG;
			break;
		case PORT_C:
			bit = SDE_PORTC_HOTPLUG;
			break;
		case PORT_D:
			bit = SDE_PORTD_HOTPLUG;
			break;
		default:
			return true;
		}
	} else {
		switch(port->port) {
		case PORT_B:
			bit = SDE_PORTB_HOTPLUG_CPT;
			break;
		case PORT_C:
			bit = SDE_PORTC_HOTPLUG_CPT;
			break;
		case PORT_D:
			bit = SDE_PORTD_HOTPLUG_CPT;
			break;
		default:
			return true;
		}
	}

	return I915_READ(SDEISR) & bit;
}