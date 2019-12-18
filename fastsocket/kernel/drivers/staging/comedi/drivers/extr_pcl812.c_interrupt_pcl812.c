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
struct comedi_device {int /*<<< orphan*/  attached; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ ai_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  interrupt_pcl812_ai_dma (int,void*) ; 
 int /*<<< orphan*/  interrupt_pcl812_ai_int (int,void*) ; 

__attribute__((used)) static irqreturn_t interrupt_pcl812(int irq, void *d)
{
	struct comedi_device *dev = d;

	if (!dev->attached) {
		comedi_error(dev, "spurious interrupt");
		return IRQ_HANDLED;
	}
	if (devpriv->ai_dma) {
		return interrupt_pcl812_ai_dma(irq, d);
	} else {
		return interrupt_pcl812_ai_int(irq, d);
	};
}