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
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_2__ {int vblank_crtc; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */

int radeon_vblank_crtc_get(struct drm_device *dev)
{
	drm_radeon_private_t *dev_priv = (drm_radeon_private_t *) dev->dev_private;

	return dev_priv->vblank_crtc;
}