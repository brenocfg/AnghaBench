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
struct comedi_device {scalar_t__ attached; scalar_t__ iobase; struct comedi_subdevice* read_subdev; } ;
struct comedi_cmd {scalar_t__ stop_src; } ;
struct comedi_async {int events; struct comedi_cmd cmd; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int status1_bits; int (* read_byte ) (scalar_t__) ;int status2_bits; scalar_t__ current_transfer; scalar_t__ count; int /*<<< orphan*/  (* write_byte ) (int,scalar_t__) ;} ;
struct TYPE_3__ {scalar_t__ register_layout; } ;

/* Variables and functions */
 int A1_TC_BIT ; 
 scalar_t__ ADC_CLEAR_REG ; 
 int COMEDI_CB_EOA ; 
 int COMEDI_CB_ERROR ; 
 int DATA_AVAIL_BIT ; 
 int DMATC_BIT ; 
 int FNHF_BIT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int OVERFLOW_BIT ; 
 int OVERRUN_BIT ; 
 scalar_t__ STATUS1_REG ; 
 scalar_t__ STATUS2_REG ; 
 int TIMER_BIT ; 
 scalar_t__ TIMER_CLEAR_REG ; 
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ TRIG_EXT ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  comedi_event (struct comedi_device*,struct comedi_subdevice*) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  handle_isa_dma (struct comedi_device*) ; 
 scalar_t__ isa_dma_transfer ; 
 scalar_t__ labpc_1200_layout ; 
 int /*<<< orphan*/  labpc_cancel (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  labpc_drain_dregs (struct comedi_device*) ; 
 int /*<<< orphan*/  labpc_drain_fifo (struct comedi_device*) ; 
 int stub1 (scalar_t__) ; 
 int stub2 (scalar_t__) ; 
 int /*<<< orphan*/  stub3 (int,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (int,scalar_t__) ; 
 int /*<<< orphan*/  stub5 (int,scalar_t__) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static irqreturn_t labpc_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct comedi_subdevice *s = dev->read_subdev;
	struct comedi_async *async;
	struct comedi_cmd *cmd;

	if (dev->attached == 0) {
		comedi_error(dev, "premature interrupt");
		return IRQ_HANDLED;
	}

	async = s->async;
	cmd = &async->cmd;
	async->events = 0;

	/*  read board status */
	devpriv->status1_bits = devpriv->read_byte(dev->iobase + STATUS1_REG);
	if (thisboard->register_layout == labpc_1200_layout)
		devpriv->status2_bits =
		    devpriv->read_byte(dev->iobase + STATUS2_REG);

	if ((devpriv->status1_bits & (DMATC_BIT | TIMER_BIT | OVERFLOW_BIT |
				      OVERRUN_BIT | DATA_AVAIL_BIT)) == 0
	    && (devpriv->status2_bits & A1_TC_BIT) == 0
	    && (devpriv->status2_bits & FNHF_BIT)) {
		return IRQ_NONE;
	}

	if (devpriv->status1_bits & OVERRUN_BIT) {
		/*  clear error interrupt */
		devpriv->write_byte(0x1, dev->iobase + ADC_CLEAR_REG);
		async->events |= COMEDI_CB_ERROR | COMEDI_CB_EOA;
		comedi_event(dev, s);
		comedi_error(dev, "overrun");
		return IRQ_HANDLED;
	}

	if (devpriv->current_transfer == isa_dma_transfer) {
		/*  if a dma terminal count of external stop trigger has occurred */
		if (devpriv->status1_bits & DMATC_BIT ||
		    (thisboard->register_layout == labpc_1200_layout
		     && devpriv->status2_bits & A1_TC_BIT)) {
			handle_isa_dma(dev);
		}
	} else
		labpc_drain_fifo(dev);

	if (devpriv->status1_bits & TIMER_BIT) {
		comedi_error(dev, "handled timer interrupt?");
		/*  clear it */
		devpriv->write_byte(0x1, dev->iobase + TIMER_CLEAR_REG);
	}

	if (devpriv->status1_bits & OVERFLOW_BIT) {
		/*  clear error interrupt */
		devpriv->write_byte(0x1, dev->iobase + ADC_CLEAR_REG);
		async->events |= COMEDI_CB_ERROR | COMEDI_CB_EOA;
		comedi_event(dev, s);
		comedi_error(dev, "overflow");
		return IRQ_HANDLED;
	}
	/*  handle external stop trigger */
	if (cmd->stop_src == TRIG_EXT) {
		if (devpriv->status2_bits & A1_TC_BIT) {
			labpc_drain_dregs(dev);
			labpc_cancel(dev, s);
			async->events |= COMEDI_CB_EOA;
		}
	}

	/* TRIG_COUNT end of acquisition */
	if (cmd->stop_src == TRIG_COUNT) {
		if (devpriv->count == 0) {
			labpc_cancel(dev, s);
			async->events |= COMEDI_CB_EOA;
		}
	}

	comedi_event(dev, s);
	return IRQ_HANDLED;
}