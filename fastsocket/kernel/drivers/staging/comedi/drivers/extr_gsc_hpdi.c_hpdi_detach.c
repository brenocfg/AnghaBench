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
struct plx_dma_desc {int dummy; } ;
struct comedi_device {scalar_t__ irq; int /*<<< orphan*/  minor; } ;
struct TYPE_2__ {scalar_t__ hw_dev; scalar_t__ hpdi_phys_iobase; int /*<<< orphan*/  dma_desc_phys_addr; scalar_t__ dma_desc; int /*<<< orphan*/ * dio_buffer_phys_addr; scalar_t__* dio_buffer; scalar_t__ hpdi_iobase; scalar_t__ plx9080_iobase; } ;

/* Variables and functions */
 int DMA_BUFFER_SIZE ; 
 unsigned int NUM_DMA_BUFFERS ; 
 int NUM_DMA_DESCRIPTORS ; 
 int /*<<< orphan*/  comedi_pci_disable (scalar_t__) ; 
 int /*<<< orphan*/  disable_plx_interrupts (struct comedi_device*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  pci_dev_put (scalar_t__) ; 
 int /*<<< orphan*/  pci_free_consistent (scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* priv (struct comedi_device*) ; 

__attribute__((used)) static int hpdi_detach(struct comedi_device *dev)
{
	unsigned int i;

	printk("comedi%d: gsc_hpdi: remove\n", dev->minor);

	if (dev->irq)
		free_irq(dev->irq, dev);
	if (priv(dev)) {
		if (priv(dev)->hw_dev) {
			if (priv(dev)->plx9080_iobase) {
				disable_plx_interrupts(dev);
				iounmap((void *)priv(dev)->plx9080_iobase);
			}
			if (priv(dev)->hpdi_iobase)
				iounmap((void *)priv(dev)->hpdi_iobase);
			/*  free pci dma buffers */
			for (i = 0; i < NUM_DMA_BUFFERS; i++) {
				if (priv(dev)->dio_buffer[i])
					pci_free_consistent(priv(dev)->hw_dev,
							    DMA_BUFFER_SIZE,
							    priv(dev)->
							    dio_buffer[i],
							    priv
							    (dev)->dio_buffer_phys_addr
							    [i]);
			}
			/*  free dma descriptors */
			if (priv(dev)->dma_desc)
				pci_free_consistent(priv(dev)->hw_dev,
						    sizeof(struct plx_dma_desc)
						    * NUM_DMA_DESCRIPTORS,
						    priv(dev)->dma_desc,
						    priv(dev)->
						    dma_desc_phys_addr);
			if (priv(dev)->hpdi_phys_iobase) {
				comedi_pci_disable(priv(dev)->hw_dev);
			}
			pci_dev_put(priv(dev)->hw_dev);
		}
	}
	return 0;
}