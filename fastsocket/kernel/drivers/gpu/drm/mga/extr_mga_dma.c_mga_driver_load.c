#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_device {int counters; int /*<<< orphan*/ * types; int /*<<< orphan*/  pdev; void* dev_private; } ;
struct TYPE_3__ {unsigned long chipset; int /*<<< orphan*/  mmio_size; int /*<<< orphan*/  mmio_base; int /*<<< orphan*/  usec_timeout; } ;
typedef  TYPE_1__ drm_mga_private_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MGA_DEFAULT_USEC_TIMEOUT ; 
 int /*<<< orphan*/  _DRM_STAT_IRQ ; 
 int /*<<< orphan*/  _DRM_STAT_PRIMARY ; 
 int /*<<< orphan*/  _DRM_STAT_SECONDARY ; 
 int drm_vblank_init (struct drm_device*,int) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mga_driver_unload (struct drm_device*) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 

int mga_driver_load(struct drm_device *dev, unsigned long flags)
{
	drm_mga_private_t *dev_priv;
	int ret;

	dev_priv = kzalloc(sizeof(drm_mga_private_t), GFP_KERNEL);
	if (!dev_priv)
		return -ENOMEM;

	dev->dev_private = (void *)dev_priv;

	dev_priv->usec_timeout = MGA_DEFAULT_USEC_TIMEOUT;
	dev_priv->chipset = flags;

	pci_set_master(dev->pdev);

	dev_priv->mmio_base = pci_resource_start(dev->pdev, 1);
	dev_priv->mmio_size = pci_resource_len(dev->pdev, 1);

	dev->counters += 3;
	dev->types[6] = _DRM_STAT_IRQ;
	dev->types[7] = _DRM_STAT_PRIMARY;
	dev->types[8] = _DRM_STAT_SECONDARY;

	ret = drm_vblank_init(dev, 1);

	if (ret) {
		(void) mga_driver_unload(dev);
		return ret;
	}

	return 0;
}