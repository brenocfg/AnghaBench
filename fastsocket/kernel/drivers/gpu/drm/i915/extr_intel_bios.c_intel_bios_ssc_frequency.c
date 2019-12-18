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
struct drm_device {int dummy; } ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 TYPE_1__* INTEL_INFO (struct drm_device*) ; 

__attribute__((used)) static int intel_bios_ssc_frequency(struct drm_device *dev,
				    bool alternate)
{
	switch (INTEL_INFO(dev)->gen) {
	case 2:
		return alternate ? 66 : 48;
	case 3:
	case 4:
		return alternate ? 100 : 96;
	default:
		return alternate ? 100 : 120;
	}
}