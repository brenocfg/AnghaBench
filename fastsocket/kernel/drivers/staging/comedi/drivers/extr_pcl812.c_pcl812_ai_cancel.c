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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {int mode_reg_int; int /*<<< orphan*/  dma; scalar_t__ ai_dma; } ;

/* Variables and functions */
 scalar_t__ PCL812_CLRINT ; 
 scalar_t__ PCL812_MODE ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  start_pacer (struct comedi_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcl812_ai_cancel(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
#ifdef PCL812_EXTDEBUG
	printk("pcl812 EDBG: BGN: pcl812_ai_cancel(...)\n");
#endif
	if (devpriv->ai_dma)
		disable_dma(devpriv->dma);
	outb(0, dev->iobase + PCL812_CLRINT);	/* clear INT request */
	outb(devpriv->mode_reg_int | 0, dev->iobase + PCL812_MODE);	/* Stop A/D */
	start_pacer(dev, -1, 0, 0);	/*  stop 8254 */
	outb(0, dev->iobase + PCL812_CLRINT);	/* clear INT request */
#ifdef PCL812_EXTDEBUG
	printk("pcl812 EDBG: END: pcl812_ai_cancel(...)\n");
#endif
	return 0;
}