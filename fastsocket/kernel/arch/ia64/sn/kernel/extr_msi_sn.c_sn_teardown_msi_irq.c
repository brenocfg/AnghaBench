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
struct sn_pcibus_provider {int /*<<< orphan*/  (* dma_unmap ) (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct sn_irq_info {scalar_t__ irq_int_bit; scalar_t__ irq_pciioinfo; } ;
struct pcidev_info {struct pci_dev* pdi_linux_pcidev; } ;
struct pcibus_bussoft {int /*<<< orphan*/  bs_base; } ;
struct pci_dev {int dummy; } ;
typedef  int nasid_t ;
struct TYPE_2__ {struct sn_irq_info* sn_irq_info; scalar_t__ pci_addr; } ;

/* Variables and functions */
 int NASID_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 struct sn_pcibus_provider* SN_PCIDEV_BUSPROVIDER (struct pci_dev*) ; 
 struct pcibus_bussoft* SN_PCIDEV_BUSSOFT (struct pci_dev*) ; 
 int SWIN_WIDGETNUM (int /*<<< orphan*/ ) ; 
 int TIO_SWIN_WIDGETNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_irq (unsigned int) ; 
 int /*<<< orphan*/  sn_intr_free (int,int,struct sn_irq_info*) ; 
 TYPE_1__* sn_msi_info ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

void sn_teardown_msi_irq(unsigned int irq)
{
	nasid_t nasid;
	int widget;
	struct pci_dev *pdev;
	struct pcidev_info *sn_pdev;
	struct sn_irq_info *sn_irq_info;
	struct pcibus_bussoft *bussoft;
	struct sn_pcibus_provider *provider;

	sn_irq_info = sn_msi_info[irq].sn_irq_info;
	if (sn_irq_info == NULL || sn_irq_info->irq_int_bit >= 0)
		return;

	sn_pdev = (struct pcidev_info *)sn_irq_info->irq_pciioinfo;
	pdev = sn_pdev->pdi_linux_pcidev;
	provider = SN_PCIDEV_BUSPROVIDER(pdev);

	(*provider->dma_unmap)(pdev,
			       sn_msi_info[irq].pci_addr,
			       PCI_DMA_FROMDEVICE);
	sn_msi_info[irq].pci_addr = 0;

	bussoft = SN_PCIDEV_BUSSOFT(pdev);
	nasid = NASID_GET(bussoft->bs_base);
	widget = (nasid & 1) ?
			TIO_SWIN_WIDGETNUM(bussoft->bs_base) :
			SWIN_WIDGETNUM(bussoft->bs_base);

	sn_intr_free(nasid, widget, sn_irq_info);
	sn_msi_info[irq].sn_irq_info = NULL;

	destroy_irq(irq);
}