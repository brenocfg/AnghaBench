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
struct i2c_adapter {int dummy; } ;
struct drm_i915_private {TYPE_1__* gmbus; } ;
struct TYPE_2__ {struct i2c_adapter adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ intel_gmbus_is_port_valid (unsigned int) ; 

struct i2c_adapter *intel_gmbus_get_adapter(struct drm_i915_private *dev_priv,
					    unsigned port)
{
	WARN_ON(!intel_gmbus_is_port_valid(port));
	/* -1 to map pin pair to gmbus index */
	return (intel_gmbus_is_port_valid(port)) ?
		&dev_priv->gmbus[port - 1].adapter : NULL;
}