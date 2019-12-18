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
typedef  int u16 ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {scalar_t__ iobase; struct comedi_subdevice* read_subdev; } ;
struct comedi_cmd {scalar_t__ stop_src; int stop_arg; int chanlist_len; } ;
struct comedi_async {int events; struct comedi_cmd cmd; } ;
struct TYPE_2__ {int adc_count; int initial_hw_count; int /*<<< orphan*/  ai_buffer; } ;

/* Variables and functions */
 int COMEDI_CB_EOA ; 
 int COMEDI_CB_ERROR ; 
 scalar_t__ DAS16M1_8254_FIRST ; 
 int FIFO_SIZE ; 
 unsigned int OVRUN ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  cfc_write_array_to_buffer (struct comedi_subdevice*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  comedi_event (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  das16m1_cancel (struct comedi_device*,struct comedi_subdevice*) ; 
 TYPE_1__* devpriv ; 
 int i8254_read (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  insw (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  munge_sample_array (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void das16m1_handler(struct comedi_device *dev, unsigned int status)
{
	struct comedi_subdevice *s;
	struct comedi_async *async;
	struct comedi_cmd *cmd;
	u16 num_samples;
	u16 hw_counter;

	s = dev->read_subdev;
	async = s->async;
	async->events = 0;
	cmd = &async->cmd;

	/*  figure out how many samples are in fifo */
	hw_counter = i8254_read(dev->iobase + DAS16M1_8254_FIRST, 0, 1);
	/* make sure hardware counter reading is not bogus due to initial value
	 * not having been loaded yet */
	if (devpriv->adc_count == 0 && hw_counter == devpriv->initial_hw_count) {
		num_samples = 0;
	} else {
		/* The calculation of num_samples looks odd, but it uses the following facts.
		 * 16 bit hardware counter is initialized with value of zero (which really
		 * means 0x1000).  The counter decrements by one on each conversion
		 * (when the counter decrements from zero it goes to 0xffff).  num_samples
		 * is a 16 bit variable, so it will roll over in a similar fashion to the
		 * hardware counter.  Work it out, and this is what you get. */
		num_samples = -hw_counter - devpriv->adc_count;
	}
	/*  check if we only need some of the points */
	if (cmd->stop_src == TRIG_COUNT) {
		if (num_samples > cmd->stop_arg * cmd->chanlist_len)
			num_samples = cmd->stop_arg * cmd->chanlist_len;
	}
	/*  make sure we dont try to get too many points if fifo has overrun */
	if (num_samples > FIFO_SIZE)
		num_samples = FIFO_SIZE;
	insw(dev->iobase, devpriv->ai_buffer, num_samples);
	munge_sample_array(devpriv->ai_buffer, num_samples);
	cfc_write_array_to_buffer(s, devpriv->ai_buffer,
				  num_samples * sizeof(short));
	devpriv->adc_count += num_samples;

	if (cmd->stop_src == TRIG_COUNT) {
		if (devpriv->adc_count >= cmd->stop_arg * cmd->chanlist_len) {	/* end of acquisition */
			das16m1_cancel(dev, s);
			async->events |= COMEDI_CB_EOA;
		}
	}

	/* this probably won't catch overruns since the card doesn't generate
	 * overrun interrupts, but we might as well try */
	if (status & OVRUN) {
		das16m1_cancel(dev, s);
		async->events |= COMEDI_CB_EOA | COMEDI_CB_ERROR;
		comedi_error(dev, "fifo overflow");
	}

	comedi_event(dev, s);

}