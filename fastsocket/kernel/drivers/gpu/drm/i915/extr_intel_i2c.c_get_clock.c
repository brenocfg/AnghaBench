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
struct intel_gmbus {int /*<<< orphan*/  gpio_reg; struct drm_i915_private* dev_priv; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int GPIO_CLOCK_DIR_MASK ; 
 int GPIO_CLOCK_VAL_IN ; 
 int I915_READ_NOTRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE_NOTRACE (int /*<<< orphan*/ ,int) ; 
 int get_reserved (struct intel_gmbus*) ; 

__attribute__((used)) static int get_clock(void *data)
{
	struct intel_gmbus *bus = data;
	struct drm_i915_private *dev_priv = bus->dev_priv;
	u32 reserved = get_reserved(bus);
	I915_WRITE_NOTRACE(bus->gpio_reg, reserved | GPIO_CLOCK_DIR_MASK);
	I915_WRITE_NOTRACE(bus->gpio_reg, reserved);
	return (I915_READ_NOTRACE(bus->gpio_reg) & GPIO_CLOCK_VAL_IN) != 0;
}