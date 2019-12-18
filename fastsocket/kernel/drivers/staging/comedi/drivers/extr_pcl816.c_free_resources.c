#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {scalar_t__ iobase; scalar_t__ irq; scalar_t__ private; } ;
struct TYPE_4__ {int /*<<< orphan*/  rtc_iosize; scalar_t__ rtc_iobase; scalar_t__ dma_rtc; scalar_t__ rtc_irq; int /*<<< orphan*/ * dmapages; scalar_t__* dmabuf; scalar_t__ dma; int /*<<< orphan*/  sub_ai; } ;
struct TYPE_3__ {int /*<<< orphan*/  io_range; } ;

/* Variables and functions */
 int RTC_lock ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  free_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  free_pages (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcl816_ai_cancel (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcl816_reset (struct comedi_device*) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* this_board ; 

__attribute__((used)) static void free_resources(struct comedi_device *dev)
{
	/* printk("free_resource()\n"); */
	if (dev->private) {
		pcl816_ai_cancel(dev, devpriv->sub_ai);
		pcl816_reset(dev);
		if (devpriv->dma)
			free_dma(devpriv->dma);
		if (devpriv->dmabuf[0])
			free_pages(devpriv->dmabuf[0], devpriv->dmapages[0]);
		if (devpriv->dmabuf[1])
			free_pages(devpriv->dmabuf[1], devpriv->dmapages[1]);
#ifdef unused
		if (devpriv->rtc_irq)
			free_irq(devpriv->rtc_irq, dev);
		if ((devpriv->dma_rtc) && (RTC_lock == 1)) {
			if (devpriv->rtc_iobase)
				release_region(devpriv->rtc_iobase,
					       devpriv->rtc_iosize);
		}
#endif
	}

	if (dev->irq)
		free_irq(dev->irq, dev);
	if (dev->iobase)
		release_region(dev->iobase, this_board->io_range);
	/* printk("free_resource() end\n"); */
}