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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int serial_interval_ns; int (* stc_readw ) (struct comedi_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dio_control; int /*<<< orphan*/  (* stc_writew ) (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dio_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIO_Control_Register ; 
 int /*<<< orphan*/  DIO_Output_Register ; 
 int /*<<< orphan*/  DIO_Parallel_Input_Register ; 
 int DIO_SDIN ; 
 int /*<<< orphan*/  DIO_SDOUT ; 
 int /*<<< orphan*/  DIO_Software_Serial_Control ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  printk (char*,unsigned char) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub4 (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ni_serial_sw_readwrite8(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   unsigned char data_out,
				   unsigned char *data_in)
{
	unsigned char mask, input = 0;

#ifdef DEBUG_DIO
	printk("ni_serial_sw_readwrite8: outputting 0x%x\n", data_out);
#endif

	/* Wait for one bit before transfer */
	udelay((devpriv->serial_interval_ns + 999) / 1000);

	for (mask = 0x80; mask; mask >>= 1) {
		/* Output current bit; note that we cannot touch s->state
		   because it is a per-subdevice field, and serial is
		   a separate subdevice from DIO. */
		devpriv->dio_output &= ~DIO_SDOUT;
		if (data_out & mask) {
			devpriv->dio_output |= DIO_SDOUT;
		}
		devpriv->stc_writew(dev, devpriv->dio_output,
				    DIO_Output_Register);

		/* Assert SDCLK (active low, inverted), wait for half of
		   the delay, deassert SDCLK, and wait for the other half. */
		devpriv->dio_control |= DIO_Software_Serial_Control;
		devpriv->stc_writew(dev, devpriv->dio_control,
				    DIO_Control_Register);

		udelay((devpriv->serial_interval_ns + 999) / 2000);

		devpriv->dio_control &= ~DIO_Software_Serial_Control;
		devpriv->stc_writew(dev, devpriv->dio_control,
				    DIO_Control_Register);

		udelay((devpriv->serial_interval_ns + 999) / 2000);

		/* Input current bit */
		if (devpriv->stc_readw(dev,
				       DIO_Parallel_Input_Register) & DIO_SDIN)
		{
/*			printk("DIO_P_I_R: 0x%x\n", devpriv->stc_readw(dev, DIO_Parallel_Input_Register)); */
			input |= mask;
		}
	}
#ifdef DEBUG_DIO
	printk("ni_serial_sw_readwrite8: inputted 0x%x\n", input);
#endif
	if (data_in)
		*data_in = input;

	return 0;
}