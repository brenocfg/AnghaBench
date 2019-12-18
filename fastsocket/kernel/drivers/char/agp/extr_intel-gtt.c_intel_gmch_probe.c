#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {scalar_t__ device; int /*<<< orphan*/  dev; } ;
struct agp_bridge_data {struct pci_dev* dev; TYPE_4__* dev_private_data; int /*<<< orphan*/ * driver; } ;
struct TYPE_9__ {scalar_t__ gmch_chip_id; int /*<<< orphan*/ * name; TYPE_1__* gtt_driver; } ;
struct TYPE_8__ {TYPE_2__* pcidev; TYPE_1__* driver; void* bridge_dev; int /*<<< orphan*/  refcount; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int dma_mask_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ find_gmch (scalar_t__) ; 
 int /*<<< orphan*/  intel_fake_agp_driver ; 
 int /*<<< orphan*/  intel_gmch_remove () ; 
 TYPE_5__* intel_gtt_chipsets ; 
 scalar_t__ intel_gtt_init () ; 
 TYPE_4__ intel_private ; 
 void* pci_dev_get (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_consistent_dma_mask (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_set_dma_mask (TYPE_2__*,int /*<<< orphan*/ ) ; 

int intel_gmch_probe(struct pci_dev *bridge_pdev, struct pci_dev *gpu_pdev,
		     struct agp_bridge_data *bridge)
{
	int i, mask;

	/*
	 * Can be called from the fake agp driver but also directly from
	 * drm/i915.ko. Hence we need to check whether everything is set up
	 * already.
	 */
	if (intel_private.driver) {
		intel_private.refcount++;
		return 1;
	}

	for (i = 0; intel_gtt_chipsets[i].name != NULL; i++) {
		if (gpu_pdev) {
			if (gpu_pdev->device ==
			    intel_gtt_chipsets[i].gmch_chip_id) {
				intel_private.pcidev = pci_dev_get(gpu_pdev);
				intel_private.driver =
					intel_gtt_chipsets[i].gtt_driver;

				break;
			}
		} else if (find_gmch(intel_gtt_chipsets[i].gmch_chip_id)) {
			intel_private.driver =
				intel_gtt_chipsets[i].gtt_driver;
			break;
		}
	}

	if (!intel_private.driver)
		return 0;

	intel_private.refcount++;

	if (bridge) {
		bridge->driver = &intel_fake_agp_driver;
		bridge->dev_private_data = &intel_private;
		bridge->dev = bridge_pdev;
	}

	intel_private.bridge_dev = pci_dev_get(bridge_pdev);

	dev_info(&bridge_pdev->dev, "Intel %s Chipset\n", intel_gtt_chipsets[i].name);

	mask = intel_private.driver->dma_mask_size;
	if (pci_set_dma_mask(intel_private.pcidev, DMA_BIT_MASK(mask)))
		dev_err(&intel_private.pcidev->dev,
			"set gfx device dma mask %d-bit failed!\n", mask);
	else
		pci_set_consistent_dma_mask(intel_private.pcidev,
					    DMA_BIT_MASK(mask));

	if (intel_gtt_init() != 0) {
		intel_gmch_remove();

		return 0;
	}

	return 1;
}