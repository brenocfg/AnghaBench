#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_device {int /*<<< orphan*/  pdev; TYPE_2__* dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  table_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  fb_aper_offset; TYPE_1__ gart_info; } ;
typedef  TYPE_2__ drm_radeon_private_t ;
typedef  int /*<<< orphan*/  drm_local_map_t ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_PCIGART_TABLE_SIZE ; 
 int /*<<< orphan*/  _DRM_FRAME_BUFFER ; 
 int /*<<< orphan*/  _DRM_WRITE_COMBINING ; 
 int drm_addmap (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int radeon_driver_firstopen(struct drm_device *dev)
{
	int ret;
	drm_local_map_t *map;
	drm_radeon_private_t *dev_priv = dev->dev_private;

	dev_priv->gart_info.table_size = RADEON_PCIGART_TABLE_SIZE;

	dev_priv->fb_aper_offset = pci_resource_start(dev->pdev, 0);
	ret = drm_addmap(dev, dev_priv->fb_aper_offset,
			 pci_resource_len(dev->pdev, 0), _DRM_FRAME_BUFFER,
			 _DRM_WRITE_COMBINING, &map);
	if (ret != 0)
		return ret;

	return 0;
}