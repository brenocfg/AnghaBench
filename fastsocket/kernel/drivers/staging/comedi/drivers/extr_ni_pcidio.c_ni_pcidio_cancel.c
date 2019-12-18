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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mite; } ;
struct TYPE_3__ {scalar_t__ daq_io_addr; } ;

/* Variables and functions */
 scalar_t__ Master_DMA_And_Interrupt_Control ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  ni_pcidio_release_di_mite_channel (struct comedi_device*) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int ni_pcidio_cancel(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	writeb(0x00,
	       devpriv->mite->daq_io_addr + Master_DMA_And_Interrupt_Control);
	ni_pcidio_release_di_mite_channel(dev);

	return 0;
}