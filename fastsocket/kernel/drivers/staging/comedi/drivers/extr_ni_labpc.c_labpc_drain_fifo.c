#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {scalar_t__ iobase; TYPE_3__* read_subdev; } ;
struct TYPE_4__ {scalar_t__ stop_src; } ;
struct comedi_async {int events; TYPE_1__ cmd; } ;
struct TYPE_6__ {struct comedi_async* async; } ;
struct TYPE_5__ {unsigned int status1_bits; unsigned int (* read_byte ) (scalar_t__) ;scalar_t__ count; } ;

/* Variables and functions */
 scalar_t__ ADC_FIFO_REG ; 
 int COMEDI_CB_EOA ; 
 int COMEDI_CB_ERROR ; 
 int DATA_AVAIL_BIT ; 
 scalar_t__ STATUS1_REG ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  cfc_write_to_buffer (TYPE_3__*,short) ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_2__* devpriv ; 
 unsigned int stub1 (scalar_t__) ; 
 unsigned int stub2 (scalar_t__) ; 
 unsigned int stub3 (scalar_t__) ; 
 unsigned int stub4 (scalar_t__) ; 

__attribute__((used)) static int labpc_drain_fifo(struct comedi_device *dev)
{
	unsigned int lsb, msb;
	short data;
	struct comedi_async *async = dev->read_subdev->async;
	const int timeout = 10000;
	unsigned int i;

	devpriv->status1_bits = devpriv->read_byte(dev->iobase + STATUS1_REG);

	for (i = 0; (devpriv->status1_bits & DATA_AVAIL_BIT) && i < timeout;
	     i++) {
		/*  quit if we have all the data we want */
		if (async->cmd.stop_src == TRIG_COUNT) {
			if (devpriv->count == 0)
				break;
			devpriv->count--;
		}
		lsb = devpriv->read_byte(dev->iobase + ADC_FIFO_REG);
		msb = devpriv->read_byte(dev->iobase + ADC_FIFO_REG);
		data = (msb << 8) | lsb;
		cfc_write_to_buffer(dev->read_subdev, data);
		devpriv->status1_bits =
		    devpriv->read_byte(dev->iobase + STATUS1_REG);
	}
	if (i == timeout) {
		comedi_error(dev, "ai timeout, fifo never empties");
		async->events |= COMEDI_CB_ERROR | COMEDI_CB_EOA;
		return -1;
	}

	return 0;
}