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
 scalar_t__ HAS_DDI (struct drm_device*) ; 
 int /*<<< orphan*/  intel_ddi_pll_init (struct drm_device*) ; 

__attribute__((used)) static void intel_cpu_pll_init(struct drm_device *dev)
{
	if (HAS_DDI(dev))
		intel_ddi_pll_init(dev);
}