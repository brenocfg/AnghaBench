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
typedef  int uint32_t ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {struct comedi_subdevice* read_subdev; } ;
struct comedi_cmd {scalar_t__ stop_src; } ;
struct comedi_async {struct comedi_cmd cmd; } ;
struct TYPE_2__ {unsigned int ai_count; scalar_t__ main_iobase; scalar_t__ dio_counter_iobase; } ;

/* Variables and functions */
 scalar_t__ ADC_FIFO_REG ; 
 scalar_t__ ADC_READ_PNTR_REG ; 
 scalar_t__ ADC_WRITE_PNTR_REG ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  cfc_write_to_buffer (struct comedi_subdevice*,int) ; 
 TYPE_1__* priv (struct comedi_device*) ; 
 int readl (scalar_t__) ; 
 int readw (scalar_t__) ; 

__attribute__((used)) static void pio_drain_ai_fifo_32(struct comedi_device *dev)
{
	struct comedi_subdevice *s = dev->read_subdev;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int i;
	unsigned int max_transfer = 100000;
	uint32_t fifo_data;
	int write_code =
	    readw(priv(dev)->main_iobase + ADC_WRITE_PNTR_REG) & 0x7fff;
	int read_code =
	    readw(priv(dev)->main_iobase + ADC_READ_PNTR_REG) & 0x7fff;

	if (cmd->stop_src == TRIG_COUNT) {
		if (max_transfer > priv(dev)->ai_count) {
			max_transfer = priv(dev)->ai_count;
		}
	}
	for (i = 0; read_code != write_code && i < max_transfer;) {
		fifo_data = readl(priv(dev)->dio_counter_iobase + ADC_FIFO_REG);
		cfc_write_to_buffer(s, fifo_data & 0xffff);
		i++;
		if (i < max_transfer) {
			cfc_write_to_buffer(s, (fifo_data >> 16) & 0xffff);
			i++;
		}
		read_code =
		    readw(priv(dev)->main_iobase + ADC_READ_PNTR_REG) & 0x7fff;
	}
	priv(dev)->ai_count -= i;
}