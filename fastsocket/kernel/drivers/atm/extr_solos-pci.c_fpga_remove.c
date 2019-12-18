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
struct solos_card {scalar_t__ config_regs; scalar_t__ buffers; int /*<<< orphan*/  tlet; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ FPGA_MODE ; 
 scalar_t__ IRQ_EN_ADDR ; 
 int /*<<< orphan*/  atm_remove (struct solos_card*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct solos_card*) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct solos_card*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct solos_card* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fpga_remove(struct pci_dev *dev)
{
	struct solos_card *card = pci_get_drvdata(dev);
	
	/* Disable IRQs */
	iowrite32(0, card->config_regs + IRQ_EN_ADDR);

	/* Reset FPGA */
	iowrite32(1, card->config_regs + FPGA_MODE);
	(void)ioread32(card->config_regs + FPGA_MODE); 

	atm_remove(card);

	free_irq(dev->irq, card);
	tasklet_kill(&card->tlet);

	/* Release device from reset */
	iowrite32(0, card->config_regs + FPGA_MODE);
	(void)ioread32(card->config_regs + FPGA_MODE); 

	pci_iounmap(dev, card->buffers);
	pci_iounmap(dev, card->config_regs);

	pci_release_regions(dev);
	pci_disable_device(dev);

	pci_set_drvdata(dev, NULL);
	kfree(card);
}