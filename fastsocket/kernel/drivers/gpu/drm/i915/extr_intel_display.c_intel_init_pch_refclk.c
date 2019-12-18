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
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HAS_PCH_CPT (struct drm_device*) ; 
 scalar_t__ HAS_PCH_IBX (struct drm_device*) ; 
 scalar_t__ HAS_PCH_LPT (struct drm_device*) ; 
 int /*<<< orphan*/  ironlake_init_pch_refclk (struct drm_device*) ; 
 int /*<<< orphan*/  lpt_init_pch_refclk (struct drm_device*) ; 

void intel_init_pch_refclk(struct drm_device *dev)
{
	if (HAS_PCH_IBX(dev) || HAS_PCH_CPT(dev))
		ironlake_init_pch_refclk(dev);
	else if (HAS_PCH_LPT(dev))
		lpt_init_pch_refclk(dev);
}