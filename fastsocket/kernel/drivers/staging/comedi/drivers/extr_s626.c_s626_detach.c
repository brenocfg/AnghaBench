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
struct comedi_device {scalar_t__ irq; } ;
struct TYPE_2__ {scalar_t__ pdev; scalar_t__ got_regions; scalar_t__ base_addr; int /*<<< orphan*/  ANABuf; int /*<<< orphan*/  RPSBuf; scalar_t__ ai_cmd_running; } ;

/* Variables and functions */
 int ACON1_BASE ; 
 int /*<<< orphan*/  CloseDMAB (struct comedi_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  DMABUF_SIZE ; 
 int IRQ_GPIO3 ; 
 int IRQ_RPS1 ; 
 int MC1_SHUTDOWN ; 
 int /*<<< orphan*/  P_ACON1 ; 
 int /*<<< orphan*/  P_IER ; 
 int /*<<< orphan*/  P_ISR ; 
 int /*<<< orphan*/  P_MC1 ; 
 int /*<<< orphan*/  WR7146 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WriteMISC2 (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_pci_disable (scalar_t__) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pci_dev_put (scalar_t__) ; 

__attribute__((used)) static int s626_detach(struct comedi_device *dev)
{
	if (devpriv) {
		/* stop ai_command */
		devpriv->ai_cmd_running = 0;

		if (devpriv->base_addr) {
			/* interrupt mask */
			WR7146(P_IER, 0);	/*  Disable master interrupt. */
			WR7146(P_ISR, IRQ_GPIO3 | IRQ_RPS1);	/*  Clear board's IRQ status flag. */

			/*  Disable the watchdog timer and battery charger. */
			WriteMISC2(dev, 0);

			/*  Close all interfaces on 7146 device. */
			WR7146(P_MC1, MC1_SHUTDOWN);
			WR7146(P_ACON1, ACON1_BASE);

			CloseDMAB(dev, &devpriv->RPSBuf, DMABUF_SIZE);
			CloseDMAB(dev, &devpriv->ANABuf, DMABUF_SIZE);
		}

		if (dev->irq)
			free_irq(dev->irq, dev);

		if (devpriv->base_addr)
			iounmap(devpriv->base_addr);

		if (devpriv->pdev) {
			if (devpriv->got_regions)
				comedi_pci_disable(devpriv->pdev);
			pci_dev_put(devpriv->pdev);
		}
	}

	DEBUG("s626_detach: S626 detached!\n");

	return 0;
}