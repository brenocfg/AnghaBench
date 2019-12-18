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
struct TYPE_2__ {int /*<<< orphan*/ * pci_dma_dev_setup; int /*<<< orphan*/ * pci_dma_bus_setup; int /*<<< orphan*/  tce_get; int /*<<< orphan*/  tce_free; int /*<<< orphan*/  tce_build; int /*<<< orphan*/  dma_set_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_FEATURE_LPAR ; 
 int /*<<< orphan*/  FW_FEATURE_MULTITCE ; 
 int /*<<< orphan*/  dma_direct_ops ; 
 int /*<<< orphan*/  dma_iommu_ops ; 
 int /*<<< orphan*/  dma_set_mask_pSeriesLP ; 
 scalar_t__ firmware_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_mem_nb ; 
 int /*<<< orphan*/  iommu_reconfig_nb ; 
 scalar_t__ of_chosen ; 
 scalar_t__ of_get_property (scalar_t__,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pSeries_reconfig_notifier_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pci_dma_bus_setup_pSeries ; 
 int /*<<< orphan*/ * pci_dma_bus_setup_pSeriesLP ; 
 int /*<<< orphan*/ * pci_dma_dev_setup_pSeries ; 
 int /*<<< orphan*/ * pci_dma_dev_setup_pSeriesLP ; 
 TYPE_1__ ppc_md ; 
 int /*<<< orphan*/  register_memory_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pci_dma_ops (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tce_build_pSeries ; 
 int /*<<< orphan*/  tce_build_pSeriesLP ; 
 int /*<<< orphan*/  tce_buildmulti_pSeriesLP ; 
 int /*<<< orphan*/  tce_free_pSeries ; 
 int /*<<< orphan*/  tce_free_pSeriesLP ; 
 int /*<<< orphan*/  tce_freemulti_pSeriesLP ; 
 int /*<<< orphan*/  tce_get_pSeriesLP ; 
 int /*<<< orphan*/  tce_get_pseries ; 

void iommu_init_early_pSeries(void)
{
	if (of_chosen && of_get_property(of_chosen, "linux,iommu-off", NULL)) {
		/* Direct I/O, IOMMU off */
		ppc_md.pci_dma_dev_setup = NULL;
		ppc_md.pci_dma_bus_setup = NULL;
		set_pci_dma_ops(&dma_direct_ops);
		return;
	}

	if (firmware_has_feature(FW_FEATURE_LPAR)) {
		if (firmware_has_feature(FW_FEATURE_MULTITCE)) {
			ppc_md.tce_build = tce_buildmulti_pSeriesLP;
			ppc_md.tce_free	 = tce_freemulti_pSeriesLP;
		} else {
			ppc_md.tce_build = tce_build_pSeriesLP;
			ppc_md.tce_free	 = tce_free_pSeriesLP;
		}
		ppc_md.tce_get   = tce_get_pSeriesLP;
		ppc_md.pci_dma_bus_setup = pci_dma_bus_setup_pSeriesLP;
		ppc_md.pci_dma_dev_setup = pci_dma_dev_setup_pSeriesLP;
		ppc_md.dma_set_mask = dma_set_mask_pSeriesLP;
	} else {
		ppc_md.tce_build = tce_build_pSeries;
		ppc_md.tce_free  = tce_free_pSeries;
		ppc_md.tce_get   = tce_get_pseries;
		ppc_md.pci_dma_bus_setup = pci_dma_bus_setup_pSeries;
		ppc_md.pci_dma_dev_setup = pci_dma_dev_setup_pSeries;
	}


	pSeries_reconfig_notifier_register(&iommu_reconfig_nb);
	register_memory_notifier(&iommu_mem_nb);

	set_pci_dma_ops(&dma_iommu_ops);
}