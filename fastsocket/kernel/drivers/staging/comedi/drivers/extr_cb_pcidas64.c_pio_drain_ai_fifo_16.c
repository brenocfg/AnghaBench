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
typedef  int uint16_t ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {struct comedi_subdevice* read_subdev; } ;
struct comedi_cmd {scalar_t__ stop_src; } ;
struct comedi_async {struct comedi_cmd cmd; } ;
struct TYPE_2__ {int ai_fifo_segment_length; int ai_count; scalar_t__ main_iobase; } ;

/* Variables and functions */
 scalar_t__ ADC_FIFO_REG ; 
 scalar_t__ ADC_READ_PNTR_REG ; 
 scalar_t__ ADC_WRITE_PNTR_REG ; 
 int /*<<< orphan*/  DEBUG_PRINT (char*,int,...) ; 
 scalar_t__ PREPOST_REG ; 
 scalar_t__ TRIG_COUNT ; 
 int adc_upper_read_ptr_code (int) ; 
 int adc_upper_write_ptr_code (int) ; 
 int /*<<< orphan*/  cfc_write_to_buffer (struct comedi_subdevice*,int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 TYPE_1__* priv (struct comedi_device*) ; 
 int readw (scalar_t__) ; 

__attribute__((used)) static void pio_drain_ai_fifo_16(struct comedi_device *dev)
{
	struct comedi_subdevice *s = dev->read_subdev;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int i;
	uint16_t prepost_bits;
	int read_segment, read_index, write_segment, write_index;
	int num_samples;

	do {
		/*  get least significant 15 bits */
		read_index =
		    readw(priv(dev)->main_iobase + ADC_READ_PNTR_REG) & 0x7fff;
		write_index =
		    readw(priv(dev)->main_iobase + ADC_WRITE_PNTR_REG) & 0x7fff;
		/* Get most significant bits (grey code).  Different boards use different code
		 * so use a scheme that doesn't depend on encoding.  This read must
		 * occur after reading least significant 15 bits to avoid race
		 * with fifo switching to next segment. */
		prepost_bits = readw(priv(dev)->main_iobase + PREPOST_REG);

		/* if read and write pointers are not on the same fifo segment, read to the
		 * end of the read segment */
		read_segment = adc_upper_read_ptr_code(prepost_bits);
		write_segment = adc_upper_write_ptr_code(prepost_bits);

		DEBUG_PRINT(" rd seg %i, wrt seg %i, rd idx %i, wrt idx %i\n",
			    read_segment, write_segment, read_index,
			    write_index);

		if (read_segment != write_segment)
			num_samples =
			    priv(dev)->ai_fifo_segment_length - read_index;
		else
			num_samples = write_index - read_index;

		if (cmd->stop_src == TRIG_COUNT) {
			if (priv(dev)->ai_count == 0)
				break;
			if (num_samples > priv(dev)->ai_count) {
				num_samples = priv(dev)->ai_count;
			}
			priv(dev)->ai_count -= num_samples;
		}

		if (num_samples < 0) {
			printk(" cb_pcidas64: bug! num_samples < 0\n");
			break;
		}

		DEBUG_PRINT(" read %i samples from fifo\n", num_samples);

		for (i = 0; i < num_samples; i++) {
			cfc_write_to_buffer(s,
					    readw(priv(dev)->main_iobase +
						  ADC_FIFO_REG));
		}

	} while (read_segment != write_segment);
}