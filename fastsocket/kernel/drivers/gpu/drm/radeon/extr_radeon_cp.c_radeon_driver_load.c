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
struct drm_device {int /*<<< orphan*/  pdev; void* dev_private; } ;
struct TYPE_3__ {unsigned long flags; int /*<<< orphan*/  mmio; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
#define  CHIP_R100 139 
#define  CHIP_R200 138 
#define  CHIP_R300 137 
#define  CHIP_R350 136 
#define  CHIP_R420 135 
#define  CHIP_R423 134 
#define  CHIP_R520 133 
#define  CHIP_R580 132 
#define  CHIP_RV200 131 
#define  CHIP_RV410 130 
#define  CHIP_RV515 129 
#define  CHIP_RV570 128 
 int /*<<< orphan*/  DRM_DEBUG (char*,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long RADEON_FAMILY_MASK ; 
 unsigned long RADEON_HAS_HIERZ ; 
 int RADEON_IS_AGP ; 
 int RADEON_IS_PCI ; 
 int RADEON_IS_PCIE ; 
 int _DRM_DRIVER ; 
 int _DRM_READ_ONLY ; 
 int /*<<< orphan*/  _DRM_REGISTERS ; 
 int drm_addmap (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ drm_pci_device_is_agp (struct drm_device*) ; 
 int drm_vblank_init (struct drm_device*,int) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_is_pcie (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_driver_unload (struct drm_device*) ; 

int radeon_driver_load(struct drm_device *dev, unsigned long flags)
{
	drm_radeon_private_t *dev_priv;
	int ret = 0;

	dev_priv = kzalloc(sizeof(drm_radeon_private_t), GFP_KERNEL);
	if (dev_priv == NULL)
		return -ENOMEM;

	dev->dev_private = (void *)dev_priv;
	dev_priv->flags = flags;

	switch (flags & RADEON_FAMILY_MASK) {
	case CHIP_R100:
	case CHIP_RV200:
	case CHIP_R200:
	case CHIP_R300:
	case CHIP_R350:
	case CHIP_R420:
	case CHIP_R423:
	case CHIP_RV410:
	case CHIP_RV515:
	case CHIP_R520:
	case CHIP_RV570:
	case CHIP_R580:
		dev_priv->flags |= RADEON_HAS_HIERZ;
		break;
	default:
		/* all other chips have no hierarchical z buffer */
		break;
	}

	pci_set_master(dev->pdev);

	if (drm_pci_device_is_agp(dev))
		dev_priv->flags |= RADEON_IS_AGP;
	else if (pci_is_pcie(dev->pdev))
		dev_priv->flags |= RADEON_IS_PCIE;
	else
		dev_priv->flags |= RADEON_IS_PCI;

	ret = drm_addmap(dev, pci_resource_start(dev->pdev, 2),
			 pci_resource_len(dev->pdev, 2), _DRM_REGISTERS,
			 _DRM_READ_ONLY | _DRM_DRIVER, &dev_priv->mmio);
	if (ret != 0)
		return ret;

	ret = drm_vblank_init(dev, 2);
	if (ret) {
		radeon_driver_unload(dev);
		return ret;
	}

	DRM_DEBUG("%s card detected\n",
		  ((dev_priv->flags & RADEON_IS_AGP) ? "AGP" : (((dev_priv->flags & RADEON_IS_PCIE) ? "PCIE" : "PCI"))));
	return ret;
}