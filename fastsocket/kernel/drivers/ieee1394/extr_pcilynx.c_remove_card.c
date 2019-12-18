#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  tq; int /*<<< orphan*/ * page_dma; int /*<<< orphan*/ * page; } ;
struct TYPE_6__ {int /*<<< orphan*/  reg_1394a; } ;
struct ti_lynx {int state; TYPE_2__ iso_rcv; int /*<<< orphan*/  pcl_mem_dma; int /*<<< orphan*/  pcl_mem; TYPE_3__* dev; int /*<<< orphan*/  rcv_page_dma; int /*<<< orphan*/  rcv_page; int /*<<< orphan*/  aux_port; int /*<<< orphan*/  local_ram; int /*<<< orphan*/  local_rom; int /*<<< orphan*/  registers; TYPE_4__* host; TYPE_1__ phyic; } ;
struct pci_dev {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  device; } ;
struct TYPE_8__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA0_CHAN_CTRL ; 
 int ISORCV_PAGES ; 
 int /*<<< orphan*/  LOCALRAM_SIZE ; 
 int /*<<< orphan*/  LONG_RESET_NO_FORCE_ROOT ; 
 int /*<<< orphan*/  MISC_CONTROL ; 
 int /*<<< orphan*/  MISC_CONTROL_SWRESET ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_INT_ENABLE ; 
 int /*<<< orphan*/  RESET_BUS ; 
#define  clear 134 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ti_lynx*) ; 
 struct device* get_device (int /*<<< orphan*/ *) ; 
 int get_phy_reg (struct ti_lynx*,int) ; 
#define  have_1394_buffers 133 
#define  have_aux_buf 132 
#define  have_intr 131 
#define  have_iomappings 130 
#define  have_pcl_mem 129 
 int /*<<< orphan*/  hpsb_remove_host (TYPE_4__*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
#define  is_host 128 
 int /*<<< orphan*/  lynx_devctl (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_consistent (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ti_lynx* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  reg_set_bits (struct ti_lynx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct ti_lynx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_phy_reg (struct ti_lynx*,int,int) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_card(struct pci_dev *dev)
{
        struct ti_lynx *lynx;
	struct device *lynx_dev;
        int i;

        lynx = pci_get_drvdata(dev);
        if (!lynx) return;
        pci_set_drvdata(dev, NULL);

	lynx_dev = get_device(&lynx->host->device);

        switch (lynx->state) {
        case is_host:
                reg_write(lynx, PCI_INT_ENABLE, 0);
                hpsb_remove_host(lynx->host);
        case have_intr:
                reg_write(lynx, PCI_INT_ENABLE, 0);
                free_irq(lynx->dev->irq, lynx);

		/* Disable IRM Contender and LCtrl */
		if (lynx->phyic.reg_1394a)
			set_phy_reg(lynx, 4, ~0xc0 & get_phy_reg(lynx, 4));

		/* Let all other nodes know to ignore us */
		lynx_devctl(lynx->host, RESET_BUS, LONG_RESET_NO_FORCE_ROOT);

        case have_iomappings:
                reg_set_bits(lynx, MISC_CONTROL, MISC_CONTROL_SWRESET);
                /* Fix buggy cards with autoboot pin not tied low: */
                reg_write(lynx, DMA0_CHAN_CTRL, 0);
                iounmap(lynx->registers);
                iounmap(lynx->local_rom);
                iounmap(lynx->local_ram);
                iounmap(lynx->aux_port);
        case have_1394_buffers:
                for (i = 0; i < ISORCV_PAGES; i++) {
                        if (lynx->iso_rcv.page[i]) {
                                pci_free_consistent(lynx->dev, PAGE_SIZE,
                                                    lynx->iso_rcv.page[i],
                                                    lynx->iso_rcv.page_dma[i]);
                        }
                }
                pci_free_consistent(lynx->dev, PAGE_SIZE, lynx->rcv_page,
                                    lynx->rcv_page_dma);
        case have_aux_buf:
        case have_pcl_mem:
                pci_free_consistent(lynx->dev, LOCALRAM_SIZE, lynx->pcl_mem,
                                    lynx->pcl_mem_dma);
        case clear:
                /* do nothing - already freed */
                ;
        }

	tasklet_kill(&lynx->iso_rcv.tq);

	if (lynx_dev)
		put_device(lynx_dev);
}