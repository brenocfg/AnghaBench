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
struct drm_device {int counters; int /*<<< orphan*/  pdev; int /*<<< orphan*/ * types; } ;

/* Variables and functions */
 int /*<<< orphan*/  _DRM_STAT_DMA ; 
 int /*<<< orphan*/  _DRM_STAT_IRQ ; 
 int /*<<< orphan*/  _DRM_STAT_PRIMARY ; 
 int /*<<< orphan*/  _DRM_STAT_SECONDARY ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 

int i810_driver_load(struct drm_device *dev, unsigned long flags)
{
	/* i810 has 4 more counters */
	dev->counters += 4;
	dev->types[6] = _DRM_STAT_IRQ;
	dev->types[7] = _DRM_STAT_PRIMARY;
	dev->types[8] = _DRM_STAT_SECONDARY;
	dev->types[9] = _DRM_STAT_DMA;

	pci_set_master(dev->pdev);

	return 0;
}