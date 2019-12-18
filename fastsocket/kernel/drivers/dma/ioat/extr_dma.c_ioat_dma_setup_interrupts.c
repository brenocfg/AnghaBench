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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; struct device dev; } ;
struct msix_entry {int entry; int /*<<< orphan*/  vector; } ;
struct TYPE_2__ {int chancnt; } ;
struct ioatdma_device {scalar_t__ reg_base; int /*<<< orphan*/  (* intr_quirk ) (struct ioatdma_device*) ;struct msix_entry* msix_entries; TYPE_1__ common; struct pci_dev* pdev; } ;
struct ioat_chan_common {scalar_t__ reg_base; int /*<<< orphan*/  (* intr_quirk ) (struct ioatdma_device*) ;struct msix_entry* msix_entries; TYPE_1__ common; struct pci_dev* pdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IOAT_INTRCTRL_MASTER_INT_EN ; 
 int /*<<< orphan*/  IOAT_INTRCTRL_MSIX_VECTOR_CONTROL ; 
 scalar_t__ IOAT_INTRCTRL_OFFSET ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_free_irq (struct device*,int /*<<< orphan*/ ,struct ioatdma_device*) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ioatdma_device*) ; 
 struct ioatdma_device* ioat_chan_by_index (struct ioatdma_device*,int) ; 
 int /*<<< orphan*/  ioat_dma_do_interrupt ; 
 int /*<<< orphan*/  ioat_dma_do_interrupt_msix ; 
 int /*<<< orphan*/  ioat_interrupt_style ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msix (struct pci_dev*) ; 
 int pci_enable_msi (struct pci_dev*) ; 
 int pci_enable_msix (struct pci_dev*,struct msix_entry*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct ioatdma_device*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ioat_dma_setup_interrupts(struct ioatdma_device *device)
{
	struct ioat_chan_common *chan;
	struct pci_dev *pdev = device->pdev;
	struct device *dev = &pdev->dev;
	struct msix_entry *msix;
	int i, j, msixcnt;
	int err = -EINVAL;
	u8 intrctrl = 0;

	if (!strcmp(ioat_interrupt_style, "msix"))
		goto msix;
	if (!strcmp(ioat_interrupt_style, "msix-single-vector"))
		goto msix_single_vector;
	if (!strcmp(ioat_interrupt_style, "msi"))
		goto msi;
	if (!strcmp(ioat_interrupt_style, "intx"))
		goto intx;
	dev_err(dev, "invalid ioat_interrupt_style %s\n", ioat_interrupt_style);
	goto err_no_irq;

msix:
	/* The number of MSI-X vectors should equal the number of channels */
	msixcnt = device->common.chancnt;
	for (i = 0; i < msixcnt; i++)
		device->msix_entries[i].entry = i;

	err = pci_enable_msix(pdev, device->msix_entries, msixcnt);
	if (err < 0)
		goto msi;
	if (err > 0)
		goto msix_single_vector;

	for (i = 0; i < msixcnt; i++) {
		msix = &device->msix_entries[i];
		chan = ioat_chan_by_index(device, i);
		err = devm_request_irq(dev, msix->vector,
				       ioat_dma_do_interrupt_msix, 0,
				       "ioat-msix", chan);
		if (err) {
			for (j = 0; j < i; j++) {
				msix = &device->msix_entries[j];
				chan = ioat_chan_by_index(device, j);
				devm_free_irq(dev, msix->vector, chan);
			}
			goto msix_single_vector;
		}
	}
	intrctrl |= IOAT_INTRCTRL_MSIX_VECTOR_CONTROL;
	goto done;

msix_single_vector:
	msix = &device->msix_entries[0];
	msix->entry = 0;
	err = pci_enable_msix(pdev, device->msix_entries, 1);
	if (err)
		goto msi;

	err = devm_request_irq(dev, msix->vector, ioat_dma_do_interrupt, 0,
			       "ioat-msix", device);
	if (err) {
		pci_disable_msix(pdev);
		goto msi;
	}
	goto done;

msi:
	err = pci_enable_msi(pdev);
	if (err)
		goto intx;

	err = devm_request_irq(dev, pdev->irq, ioat_dma_do_interrupt, 0,
			       "ioat-msi", device);
	if (err) {
		pci_disable_msi(pdev);
		goto intx;
	}
	goto done;

intx:
	err = devm_request_irq(dev, pdev->irq, ioat_dma_do_interrupt,
			       IRQF_SHARED, "ioat-intx", device);
	if (err)
		goto err_no_irq;

done:
	if (device->intr_quirk)
		device->intr_quirk(device);
	intrctrl |= IOAT_INTRCTRL_MASTER_INT_EN;
	writeb(intrctrl, device->reg_base + IOAT_INTRCTRL_OFFSET);
	return 0;

err_no_irq:
	/* Disable all interrupt generation */
	writeb(0, device->reg_base + IOAT_INTRCTRL_OFFSET);
	dev_err(dev, "no usable interrupts\n");
	return err;
}