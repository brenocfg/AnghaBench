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
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int serial_hw_mode; int dio_control; unsigned int serial_interval_ns; int clock_and_fout; int /*<<< orphan*/  (* stc_writew ) (struct comedi_device*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Clock_and_FOUT_Register ; 
 int /*<<< orphan*/  DIO_Control_Register ; 
 int DIO_HW_Serial_Enable ; 
 int DIO_HW_Serial_Timebase ; 
 int DIO_Serial_Out_Divide_By_2 ; 
 int DIO_Software_Serial_Control ; 
 int EINVAL ; 
#define  INSN_CONFIG_BIDIRECTIONAL_DATA 129 
#define  INSN_CONFIG_SERIAL_CLOCK 128 
 unsigned int SERIAL_10US ; 
 unsigned int SERIAL_1_2US ; 
 unsigned int SERIAL_600NS ; 
 unsigned int SERIAL_DISABLED ; 
 int Slow_Internal_Timebase ; 
 TYPE_1__* devpriv ; 
 int ni_serial_hw_readwrite8 (struct comedi_device*,struct comedi_subdevice*,unsigned char,unsigned char*) ; 
 int ni_serial_sw_readwrite8 (struct comedi_device*,struct comedi_subdevice*,unsigned char,unsigned char*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_serial_insn_config(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn, unsigned int *data)
{
	int err = insn->n;
	unsigned char byte_out, byte_in = 0;

	if (insn->n != 2)
		return -EINVAL;

	switch (data[0]) {
	case INSN_CONFIG_SERIAL_CLOCK:

#ifdef DEBUG_DIO
		printk("SPI serial clock Config cd\n", data[1]);
#endif
		devpriv->serial_hw_mode = 1;
		devpriv->dio_control |= DIO_HW_Serial_Enable;

		if (data[1] == SERIAL_DISABLED) {
			devpriv->serial_hw_mode = 0;
			devpriv->dio_control &= ~(DIO_HW_Serial_Enable |
						  DIO_Software_Serial_Control);
			data[1] = SERIAL_DISABLED;
			devpriv->serial_interval_ns = data[1];
		} else if (data[1] <= SERIAL_600NS) {
			/* Warning: this clock speed is too fast to reliably
			   control SCXI. */
			devpriv->dio_control &= ~DIO_HW_Serial_Timebase;
			devpriv->clock_and_fout |= Slow_Internal_Timebase;
			devpriv->clock_and_fout &= ~DIO_Serial_Out_Divide_By_2;
			data[1] = SERIAL_600NS;
			devpriv->serial_interval_ns = data[1];
		} else if (data[1] <= SERIAL_1_2US) {
			devpriv->dio_control &= ~DIO_HW_Serial_Timebase;
			devpriv->clock_and_fout |= Slow_Internal_Timebase |
			    DIO_Serial_Out_Divide_By_2;
			data[1] = SERIAL_1_2US;
			devpriv->serial_interval_ns = data[1];
		} else if (data[1] <= SERIAL_10US) {
			devpriv->dio_control |= DIO_HW_Serial_Timebase;
			devpriv->clock_and_fout |= Slow_Internal_Timebase |
			    DIO_Serial_Out_Divide_By_2;
			/* Note: DIO_Serial_Out_Divide_By_2 only affects
			   600ns/1.2us. If you turn divide_by_2 off with the
			   slow clock, you will still get 10us, except then
			   all your delays are wrong. */
			data[1] = SERIAL_10US;
			devpriv->serial_interval_ns = data[1];
		} else {
			devpriv->dio_control &= ~(DIO_HW_Serial_Enable |
						  DIO_Software_Serial_Control);
			devpriv->serial_hw_mode = 0;
			data[1] = (data[1] / 1000) * 1000;
			devpriv->serial_interval_ns = data[1];
		}

		devpriv->stc_writew(dev, devpriv->dio_control,
				    DIO_Control_Register);
		devpriv->stc_writew(dev, devpriv->clock_and_fout,
				    Clock_and_FOUT_Register);
		return 1;

		break;

	case INSN_CONFIG_BIDIRECTIONAL_DATA:

		if (devpriv->serial_interval_ns == 0) {
			return -EINVAL;
		}

		byte_out = data[1] & 0xFF;

		if (devpriv->serial_hw_mode) {
			err = ni_serial_hw_readwrite8(dev, s, byte_out,
						      &byte_in);
		} else if (devpriv->serial_interval_ns > 0) {
			err = ni_serial_sw_readwrite8(dev, s, byte_out,
						      &byte_in);
		} else {
			printk("ni_serial_insn_config: serial disabled!\n");
			return -EINVAL;
		}
		if (err < 0)
			return err;
		data[1] = byte_in & 0xFF;
		return insn->n;

		break;
	default:
		return -EINVAL;
	}

}