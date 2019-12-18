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
struct drm_device {int /*<<< orphan*/  dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIGART_FILE_PRIV ; 
 int /*<<< orphan*/  radeon_do_release (struct drm_device*) ; 
 int /*<<< orphan*/  radeon_surfaces_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void radeon_driver_lastclose(struct drm_device *dev)
{
	radeon_surfaces_release(PCIGART_FILE_PRIV, dev->dev_private);
	radeon_do_release(dev);
}