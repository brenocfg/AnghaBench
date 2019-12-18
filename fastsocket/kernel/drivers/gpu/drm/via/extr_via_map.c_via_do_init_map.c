#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct drm_device {TYPE_1__* dev_private; } ;
typedef  int /*<<< orphan*/  drm_via_sarea_t ;
struct TYPE_6__ {int /*<<< orphan*/  agpAddr; TYPE_5__* sarea; int /*<<< orphan*/ * sarea_priv; void* mmio; void* fb; } ;
typedef  TYPE_1__ drm_via_private_t ;
struct TYPE_7__ {int sarea_priv_offset; int /*<<< orphan*/  agpAddr; int /*<<< orphan*/  mmio_offset; int /*<<< orphan*/  fb_offset; } ;
typedef  TYPE_2__ drm_via_init_t ;
struct TYPE_8__ {scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 void* drm_core_findmap (struct drm_device*,int /*<<< orphan*/ ) ; 
 TYPE_5__* drm_getsarea (struct drm_device*) ; 
 int /*<<< orphan*/  via_do_cleanup_map (struct drm_device*) ; 
 int /*<<< orphan*/  via_init_dmablit (struct drm_device*) ; 
 int /*<<< orphan*/  via_init_futex (TYPE_1__*) ; 

__attribute__((used)) static int via_do_init_map(struct drm_device *dev, drm_via_init_t *init)
{
	drm_via_private_t *dev_priv = dev->dev_private;

	DRM_DEBUG("\n");

	dev_priv->sarea = drm_getsarea(dev);
	if (!dev_priv->sarea) {
		DRM_ERROR("could not find sarea!\n");
		dev->dev_private = (void *)dev_priv;
		via_do_cleanup_map(dev);
		return -EINVAL;
	}

	dev_priv->fb = drm_core_findmap(dev, init->fb_offset);
	if (!dev_priv->fb) {
		DRM_ERROR("could not find framebuffer!\n");
		dev->dev_private = (void *)dev_priv;
		via_do_cleanup_map(dev);
		return -EINVAL;
	}
	dev_priv->mmio = drm_core_findmap(dev, init->mmio_offset);
	if (!dev_priv->mmio) {
		DRM_ERROR("could not find mmio region!\n");
		dev->dev_private = (void *)dev_priv;
		via_do_cleanup_map(dev);
		return -EINVAL;
	}

	dev_priv->sarea_priv =
	    (drm_via_sarea_t *) ((u8 *) dev_priv->sarea->handle +
				 init->sarea_priv_offset);

	dev_priv->agpAddr = init->agpAddr;

	via_init_futex(dev_priv);

	via_init_dmablit(dev);

	dev->dev_private = (void *)dev_priv;
	return 0;
}