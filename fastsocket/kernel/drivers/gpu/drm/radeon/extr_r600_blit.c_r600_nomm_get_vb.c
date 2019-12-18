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
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  blit_vb; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  radeon_freelist_get (struct drm_device*) ; 

__attribute__((used)) static int r600_nomm_get_vb(struct drm_device *dev)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	dev_priv->blit_vb = radeon_freelist_get(dev);
	if (!dev_priv->blit_vb) {
		DRM_ERROR("Unable to allocate vertex buffer for blit\n");
		return -EAGAIN;
	}
	return 0;
}