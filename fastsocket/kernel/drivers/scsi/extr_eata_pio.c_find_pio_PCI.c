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
struct pci_dev {int dummy; } ;
struct get_conf {scalar_t__ FORCADR; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,int /*<<< orphan*/ ) ; 
 scalar_t__ DBG_PCI ; 
 scalar_t__ DBG_PROBE ; 
 scalar_t__* EISAbases ; 
 unsigned long IORESOURCE_MEM ; 
 unsigned long* ISAbases ; 
 unsigned long MAXISA ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_DPT ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_DPT ; 
 scalar_t__ check_blink_state (unsigned long) ; 
 scalar_t__ get_pio_conf_PIO (unsigned long,struct get_conf*) ; 
 int inb (unsigned long) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 unsigned long pci_resource_flags (struct pci_dev*,int /*<<< orphan*/ ) ; 
 unsigned long pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  register_pio_HBA (unsigned long,struct get_conf*,struct pci_dev*) ; 
 int /*<<< orphan*/  release_region (unsigned long,int) ; 

__attribute__((used)) static void find_pio_PCI(struct get_conf *buf)
{
#ifndef CONFIG_PCI
	printk("eata_dma: kernel PCI support not enabled. Skipping scan for PCI HBAs.\n");
#else
	struct pci_dev *dev = NULL;
	unsigned long base, x;

	while ((dev = pci_get_device(PCI_VENDOR_ID_DPT, PCI_DEVICE_ID_DPT, dev)) != NULL) {
		DBG(DBG_PROBE && DBG_PCI, printk("eata_pio: find_PCI, HBA at %s\n", pci_name(dev)));
		if (pci_enable_device(dev))
			continue;
		pci_set_master(dev);
		base = pci_resource_flags(dev, 0);
		if (base & IORESOURCE_MEM) {
			printk("eata_pio: invalid base address of device %s\n", pci_name(dev));
			continue;
		}
		base = pci_resource_start(dev, 0);
		/* EISA tag there ? */
		if ((inb(base) == 0x12) && (inb(base + 1) == 0x14))
			continue;	/* Jep, it's forced, so move on  */
		base += 0x10;	/* Now, THIS is the real address */
		if (base != 0x1f8) {
			/* We didn't find it in the primary search */
			if (get_pio_conf_PIO(base, buf)) {
				if (buf->FORCADR) {	/* If the address is forced */
					release_region(base, 9);
					continue;	/* we'll find it later      */
				}

				/* OK. We made it till here, so we can go now  
				 * and register it. We  only have to check and 
				 * eventually remove it from the EISA and ISA list 
				 */

				if (!register_pio_HBA(base, buf, dev)) {
					release_region(base, 9);
					continue;
				}

				if (base < 0x1000) {
					for (x = 0; x < MAXISA; ++x) {
						if (ISAbases[x] == base) {
							ISAbases[x] = 0;
							break;
						}
					}
				} else if ((base & 0x0fff) == 0x0c88) {
					x = (base >> 12) & 0x0f;
					EISAbases[x] = 0;
				}
			}
#ifdef CHECK_BLINK
			else if (check_blink_state(base)) {
				printk("eata_pio: HBA is in BLINK state.\n" "Consult your HBAs manual to correct this.\n");
			}
#endif
		}
	}
#endif				/* #ifndef CONFIG_PCI */
}