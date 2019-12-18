#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  stopper; } ;
struct cx8802_dev {TYPE_1__ mpegq; TYPE_2__* pci; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  btcx_riscmem_free (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx8802_stop_dma (struct cx8802_dev*) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct cx8802_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_set_drvdata (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cx8802_fini_common(struct cx8802_dev *dev)
{
	dprintk( 2, "cx8802_fini_common\n" );
	cx8802_stop_dma(dev);
	pci_disable_device(dev->pci);

	/* unregister stuff */
	free_irq(dev->pci->irq, dev);
	pci_set_drvdata(dev->pci, NULL);

	/* free memory */
	btcx_riscmem_free(dev->pci,&dev->mpegq.stopper);
}