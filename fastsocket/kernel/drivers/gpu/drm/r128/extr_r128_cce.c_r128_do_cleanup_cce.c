#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_device {TYPE_1__* dev_private; int /*<<< orphan*/ * agp_buffer_map; scalar_t__ irq_enabled; } ;
struct TYPE_5__ {scalar_t__ bus_addr; } ;
struct TYPE_4__ {TYPE_3__ gart_info; int /*<<< orphan*/ * ring_rptr; int /*<<< orphan*/ * cce_ring; int /*<<< orphan*/  is_pci; } ;
typedef  TYPE_1__ drm_r128_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  drm_ati_pcigart_cleanup (struct drm_device*,TYPE_3__*) ; 
 int /*<<< orphan*/  drm_core_ioremapfree (int /*<<< orphan*/ *,struct drm_device*) ; 
 int /*<<< orphan*/  drm_irq_uninstall (struct drm_device*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

int r128_do_cleanup_cce(struct drm_device *dev)
{

	/* Make sure interrupts are disabled here because the uninstall ioctl
	 * may not have been called from userspace and after dev_private
	 * is freed, it's too late.
	 */
	if (dev->irq_enabled)
		drm_irq_uninstall(dev);

	if (dev->dev_private) {
		drm_r128_private_t *dev_priv = dev->dev_private;

#if __OS_HAS_AGP
		if (!dev_priv->is_pci) {
			if (dev_priv->cce_ring != NULL)
				drm_core_ioremapfree(dev_priv->cce_ring, dev);
			if (dev_priv->ring_rptr != NULL)
				drm_core_ioremapfree(dev_priv->ring_rptr, dev);
			if (dev->agp_buffer_map != NULL) {
				drm_core_ioremapfree(dev->agp_buffer_map, dev);
				dev->agp_buffer_map = NULL;
			}
		} else
#endif
		{
			if (dev_priv->gart_info.bus_addr)
				if (!drm_ati_pcigart_cleanup(dev,
							&dev_priv->gart_info))
					DRM_ERROR
					    ("failed to cleanup PCI GART!\n");
		}

		kfree(dev->dev_private);
		dev->dev_private = NULL;
	}

	return 0;
}