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
struct comedi_device {int /*<<< orphan*/  spinlock; } ;
struct comedi_cmd {scalar_t__ stop_src; } ;
struct comedi_async {int /*<<< orphan*/ * inttrig; struct comedi_cmd cmd; } ;
struct TYPE_4__ {unsigned int ao_count; int adc_fifo_bits; int ao_control_bits; scalar_t__ control_status; int /*<<< orphan*/  ao_buffer; scalar_t__ ao_registers; } ;
struct TYPE_3__ {unsigned int fifo_size; } ;

/* Variables and functions */
 scalar_t__ DACDATA ; 
 int DACEN ; 
 scalar_t__ DAC_CSR ; 
 int DAC_EMPTY ; 
 int DAC_START ; 
 int DAEMI ; 
 int DAEMIE ; 
 int DAHFI ; 
 int DAHFIE ; 
 int EINVAL ; 
 scalar_t__ INT_ADCFIFO ; 
 scalar_t__ TRIG_COUNT ; 
 unsigned int cfc_read_array_from_buffer (struct comedi_subdevice*,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  outsw (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static int cb_pcidas_ao_inttrig(struct comedi_device *dev,
				struct comedi_subdevice *s,
				unsigned int trig_num)
{
	unsigned int num_bytes, num_points = thisboard->fifo_size;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned long flags;

	if (trig_num != 0)
		return -EINVAL;

	/*  load up fifo */
	if (cmd->stop_src == TRIG_COUNT && devpriv->ao_count < num_points)
		num_points = devpriv->ao_count;

	num_bytes = cfc_read_array_from_buffer(s, devpriv->ao_buffer,
					       num_points * sizeof(short));
	num_points = num_bytes / sizeof(short);

	if (cmd->stop_src == TRIG_COUNT) {
		devpriv->ao_count -= num_points;
	}
	/*  write data to board's fifo */
	outsw(devpriv->ao_registers + DACDATA, devpriv->ao_buffer, num_bytes);

	/*  enable dac half-full and empty interrupts */
	spin_lock_irqsave(&dev->spinlock, flags);
	devpriv->adc_fifo_bits |= DAEMIE | DAHFIE;
#ifdef CB_PCIDAS_DEBUG
	printk("comedi: adc_fifo_bits are 0x%x\n", devpriv->adc_fifo_bits);
#endif
	/*  enable and clear interrupts */
	outw(devpriv->adc_fifo_bits | DAEMI | DAHFI,
	     devpriv->control_status + INT_ADCFIFO);

	/*  start dac */
	devpriv->ao_control_bits |= DAC_START | DACEN | DAC_EMPTY;
	outw(devpriv->ao_control_bits, devpriv->control_status + DAC_CSR);
#ifdef CB_PCIDAS_DEBUG
	printk("comedi: sent 0x%x to dac control\n", devpriv->ao_control_bits);
#endif
	spin_unlock_irqrestore(&dev->spinlock, flags);

	async->inttrig = NULL;

	return 0;
}