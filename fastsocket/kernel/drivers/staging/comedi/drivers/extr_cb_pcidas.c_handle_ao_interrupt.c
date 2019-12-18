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
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; struct comedi_subdevice* write_subdev; } ;
struct comedi_cmd {scalar_t__ stop_src; } ;
struct comedi_async {struct comedi_cmd cmd; int /*<<< orphan*/  events; } ;
struct TYPE_4__ {unsigned int adc_fifo_bits; unsigned int ao_count; scalar_t__ control_status; int /*<<< orphan*/  ao_buffer; scalar_t__ ao_registers; } ;
struct TYPE_3__ {int fifo_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 scalar_t__ DACDATA ; 
 scalar_t__ DAC_CSR ; 
 int DAC_EMPTY ; 
 unsigned int DAEMI ; 
 unsigned int DAHFI ; 
 scalar_t__ INT_ADCFIFO ; 
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ TRIG_NONE ; 
 int /*<<< orphan*/  cb_pcidas_ao_cancel (struct comedi_device*,struct comedi_subdevice*) ; 
 unsigned int cfc_read_array_from_buffer (struct comedi_subdevice*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  comedi_event (struct comedi_device*,struct comedi_subdevice*) ; 
 TYPE_2__* devpriv ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outsw (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static void handle_ao_interrupt(struct comedi_device *dev, unsigned int status)
{
	struct comedi_subdevice *s = dev->write_subdev;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int half_fifo = thisboard->fifo_size / 2;
	unsigned int num_points;
	unsigned long flags;

	async->events = 0;

	if (status & DAEMI) {
		/*  clear dac empty interrupt latch */
		spin_lock_irqsave(&dev->spinlock, flags);
		outw(devpriv->adc_fifo_bits | DAEMI,
		     devpriv->control_status + INT_ADCFIFO);
		spin_unlock_irqrestore(&dev->spinlock, flags);
		if (inw(devpriv->ao_registers + DAC_CSR) & DAC_EMPTY) {
			if (cmd->stop_src == TRIG_NONE ||
			    (cmd->stop_src == TRIG_COUNT
			     && devpriv->ao_count)) {
				comedi_error(dev, "dac fifo underflow");
				cb_pcidas_ao_cancel(dev, s);
				async->events |= COMEDI_CB_ERROR;
			}
			async->events |= COMEDI_CB_EOA;
		}
	} else if (status & DAHFI) {
		unsigned int num_bytes;

		/*  figure out how many points we are writing to fifo */
		num_points = half_fifo;
		if (cmd->stop_src == TRIG_COUNT &&
		    devpriv->ao_count < num_points)
			num_points = devpriv->ao_count;
		num_bytes =
		    cfc_read_array_from_buffer(s, devpriv->ao_buffer,
					       num_points * sizeof(short));
		num_points = num_bytes / sizeof(short);

		if (async->cmd.stop_src == TRIG_COUNT) {
			devpriv->ao_count -= num_points;
		}
		/*  write data to board's fifo */
		outsw(devpriv->ao_registers + DACDATA, devpriv->ao_buffer,
		      num_points);
		/*  clear half-full interrupt latch */
		spin_lock_irqsave(&dev->spinlock, flags);
		outw(devpriv->adc_fifo_bits | DAHFI,
		     devpriv->control_status + INT_ADCFIFO);
		spin_unlock_irqrestore(&dev->spinlock, flags);
	}

	comedi_event(dev, s);
}