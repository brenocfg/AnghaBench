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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {struct pci_dev* misc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD64_GARTAPERTURECTL ; 
 int /*<<< orphan*/  AMD_NB_GART ; 
 int /*<<< orphan*/  GARTEN ; 
 int /*<<< orphan*/  amd_nb_has_feature (int /*<<< orphan*/ ) ; 
 int amd_nb_num () ; 
 int /*<<< orphan*/ * dma_ops ; 
 int /*<<< orphan*/  gart_dma_ops ; 
 scalar_t__ no_agp ; 
 TYPE_1__* node_to_amd_nb (int) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gart_iommu_shutdown(void)
{
	struct pci_dev *dev;
	int i;

	if (no_agp && (dma_ops != &gart_dma_ops))
		return;

	if (!amd_nb_has_feature(AMD_NB_GART))
		return;

	for (i = 0; i < amd_nb_num(); i++) {
		u32 ctl;

		dev = node_to_amd_nb(i)->misc;
		pci_read_config_dword(dev, AMD64_GARTAPERTURECTL, &ctl);

		ctl &= ~GARTEN;

		pci_write_config_dword(dev, AMD64_GARTAPERTURECTL, ctl);
	}
}