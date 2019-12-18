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
struct drm_device {int max_vblank_count; } ;

/* Variables and functions */

int radeon_driver_irq_postinstall_kms(struct drm_device *dev)
{
	dev->max_vblank_count = 0x001fffff;
	return 0;
}