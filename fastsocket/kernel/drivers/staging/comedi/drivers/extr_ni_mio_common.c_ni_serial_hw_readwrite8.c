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
struct TYPE_2__ {unsigned int (* stc_readw ) (struct comedi_device*,int /*<<< orphan*/ ) ;int serial_interval_ns; int /*<<< orphan*/  dio_control; int /*<<< orphan*/  (* stc_writew ) (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dio_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIO_Control_Register ; 
 int /*<<< orphan*/  DIO_HW_Serial_Start ; 
 int /*<<< orphan*/  DIO_Output_Register ; 
 int /*<<< orphan*/  DIO_Serial_Data_Mask ; 
 int /*<<< orphan*/  DIO_Serial_Data_Out (unsigned char) ; 
 unsigned int DIO_Serial_IO_In_Progress_St ; 
 int /*<<< orphan*/  DIO_Serial_Input_Register ; 
 int EBUSY ; 
 int ETIME ; 
 int /*<<< orphan*/  Joint_Status_1_Register ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int stub2 (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int stub4 (struct comedi_device*,int /*<<< orphan*/ ) ; 
 unsigned char stub5 (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ni_serial_hw_readwrite8(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   unsigned char data_out,
				   unsigned char *data_in)
{
	unsigned int status1;
	int err = 0, count = 20;

#ifdef DEBUG_DIO
	printk("ni_serial_hw_readwrite8: outputting 0x%x\n", data_out);
#endif

	devpriv->dio_output &= ~DIO_Serial_Data_Mask;
	devpriv->dio_output |= DIO_Serial_Data_Out(data_out);
	devpriv->stc_writew(dev, devpriv->dio_output, DIO_Output_Register);

	status1 = devpriv->stc_readw(dev, Joint_Status_1_Register);
	if (status1 & DIO_Serial_IO_In_Progress_St) {
		err = -EBUSY;
		goto Error;
	}

	devpriv->dio_control |= DIO_HW_Serial_Start;
	devpriv->stc_writew(dev, devpriv->dio_control, DIO_Control_Register);
	devpriv->dio_control &= ~DIO_HW_Serial_Start;

	/* Wait until STC says we're done, but don't loop infinitely. */
	while ((status1 =
		devpriv->stc_readw(dev,
				   Joint_Status_1_Register)) &
	       DIO_Serial_IO_In_Progress_St) {
		/* Delay one bit per loop */
		udelay((devpriv->serial_interval_ns + 999) / 1000);
		if (--count < 0) {
			printk
			    ("ni_serial_hw_readwrite8: SPI serial I/O didn't finish in time!\n");
			err = -ETIME;
			goto Error;
		}
	}

	/* Delay for last bit. This delay is absolutely necessary, because
	   DIO_Serial_IO_In_Progress_St goes high one bit too early. */
	udelay((devpriv->serial_interval_ns + 999) / 1000);

	if (data_in != NULL) {
		*data_in = devpriv->stc_readw(dev, DIO_Serial_Input_Register);
#ifdef DEBUG_DIO
		printk("ni_serial_hw_readwrite8: inputted 0x%x\n", *data_in);
#endif
	}

Error:
	devpriv->stc_writew(dev, devpriv->dio_control, DIO_Control_Register);

	return err;
}