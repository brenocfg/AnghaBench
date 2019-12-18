#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device {TYPE_2__* dev_private; } ;
struct TYPE_5__ {TYPE_1__* blit_vb; } ;
typedef  TYPE_2__ drm_radeon_private_t ;
struct TYPE_4__ {struct drm_file* file_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int r600_nomm_get_vb (struct drm_device*) ; 
 int /*<<< orphan*/  set_default_state (TYPE_2__*) ; 
 int /*<<< orphan*/  set_shaders (struct drm_device*) ; 

int
r600_prepare_blit_copy(struct drm_device *dev, struct drm_file *file_priv)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	int ret;
	DRM_DEBUG("\n");

	ret = r600_nomm_get_vb(dev);
	if (ret)
		return ret;

	dev_priv->blit_vb->file_priv = file_priv;

	set_default_state(dev_priv);
	set_shaders(dev);

	return 0;
}