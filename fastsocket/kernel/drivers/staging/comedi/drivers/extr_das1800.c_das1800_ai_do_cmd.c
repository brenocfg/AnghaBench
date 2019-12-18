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
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  irq; } ;
struct comedi_cmd {int flags; scalar_t__ stop_src; int stop_arg; int chanlist_len; int convert_arg; } ;
struct comedi_async {struct comedi_cmd cmd; } ;
struct TYPE_2__ {int irq_dma_bits; int dma_bits; int count; } ;

/* Variables and functions */
 int BMDE ; 
 int CVEN ; 
 scalar_t__ DAS1800_BURST_LENGTH ; 
 scalar_t__ DAS1800_BURST_RATE ; 
 scalar_t__ DAS1800_CONTROL_A ; 
 scalar_t__ DAS1800_CONTROL_B ; 
 scalar_t__ DAS1800_CONTROL_C ; 
 scalar_t__ DAS1800_STATUS ; 
 int DMA_ENABLED ; 
 int FIMD ; 
 scalar_t__ TRIG_COUNT ; 
 int TRIG_RT ; 
 int TRIG_WAKE_EOS ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int control_a_bits (struct comedi_cmd) ; 
 int control_c_bits (struct comedi_cmd) ; 
 int /*<<< orphan*/  das1800_cancel (struct comedi_device*,struct comedi_subdevice*) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  program_chanlist (struct comedi_device*,struct comedi_cmd) ; 
 int setup_counters (struct comedi_device*,struct comedi_cmd) ; 
 int /*<<< orphan*/  setup_dma (struct comedi_device*,struct comedi_cmd) ; 

__attribute__((used)) static int das1800_ai_do_cmd(struct comedi_device *dev,
			     struct comedi_subdevice *s)
{
	int ret;
	int control_a, control_c;
	struct comedi_async *async = s->async;
	struct comedi_cmd cmd = async->cmd;

	if (!dev->irq) {
		comedi_error(dev,
			     "no irq assigned for das-1800, cannot do hardware conversions");
		return -1;
	}

	/* disable dma on TRIG_WAKE_EOS, or TRIG_RT
	 * (because dma in handler is unsafe at hard real-time priority) */
	if (cmd.flags & (TRIG_WAKE_EOS | TRIG_RT)) {
		devpriv->irq_dma_bits &= ~DMA_ENABLED;
	} else {
		devpriv->irq_dma_bits |= devpriv->dma_bits;
	}
	/*  interrupt on end of conversion for TRIG_WAKE_EOS */
	if (cmd.flags & TRIG_WAKE_EOS) {
		/*  interrupt fifo not empty */
		devpriv->irq_dma_bits &= ~FIMD;
	} else {
		/*  interrupt fifo half full */
		devpriv->irq_dma_bits |= FIMD;
	}
	/*  determine how many conversions we need */
	if (cmd.stop_src == TRIG_COUNT) {
		devpriv->count = cmd.stop_arg * cmd.chanlist_len;
	}

	das1800_cancel(dev, s);

	/*  determine proper bits for control registers */
	control_a = control_a_bits(cmd);
	control_c = control_c_bits(cmd);

	/* setup card and start */
	program_chanlist(dev, cmd);
	ret = setup_counters(dev, cmd);
	if (ret < 0) {
		comedi_error(dev, "Error setting up counters");
		return ret;
	}
	setup_dma(dev, cmd);
	outb(control_c, dev->iobase + DAS1800_CONTROL_C);
	/*  set conversion rate and length for burst mode */
	if (control_c & BMDE) {
		/*  program conversion period with number of microseconds minus 1 */
		outb(cmd.convert_arg / 1000 - 1,
		     dev->iobase + DAS1800_BURST_RATE);
		outb(cmd.chanlist_len - 1, dev->iobase + DAS1800_BURST_LENGTH);
	}
	outb(devpriv->irq_dma_bits, dev->iobase + DAS1800_CONTROL_B);	/*  enable irq/dma */
	outb(control_a, dev->iobase + DAS1800_CONTROL_A);	/* enable fifo and triggering */
	outb(CVEN, dev->iobase + DAS1800_STATUS);	/* enable conversions */

	return 0;
}