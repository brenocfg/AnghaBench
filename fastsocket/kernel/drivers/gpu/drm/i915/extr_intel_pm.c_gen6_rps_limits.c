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
struct TYPE_2__ {int max_delay; int min_delay; } ;
struct drm_i915_private {TYPE_1__ rps; } ;

/* Variables and functions */

__attribute__((used)) static u32 gen6_rps_limits(struct drm_i915_private *dev_priv, u8 *val)
{
	u32 limits;

	limits = 0;

	if (*val >= dev_priv->rps.max_delay)
		*val = dev_priv->rps.max_delay;
	limits |= dev_priv->rps.max_delay << 24;

	/* Only set the down limit when we've reached the lowest level to avoid
	 * getting more interrupts, otherwise leave this clear. This prevents a
	 * race in the hw when coming out of rc6: There's a tiny window where
	 * the hw runs at the minimal clock before selecting the desired
	 * frequency, if the down threshold expires in that window we will not
	 * receive a down interrupt. */
	if (*val <= dev_priv->rps.min_delay) {
		*val = dev_priv->rps.min_delay;
		limits |= dev_priv->rps.min_delay << 16;
	}

	return limits;
}