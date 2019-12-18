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
struct comedi_subdevice {unsigned int state; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {unsigned int (* stc_readw ) (struct comedi_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dio_output; int /*<<< orphan*/  (* stc_writew ) (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ serial_interval_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIO_Output_Register ; 
 int /*<<< orphan*/  DIO_Parallel_Data_Mask ; 
 int /*<<< orphan*/  DIO_Parallel_Data_Out (unsigned int) ; 
 int /*<<< orphan*/  DIO_Parallel_Input_Register ; 
 unsigned int DIO_SDIN ; 
 unsigned int DIO_SDOUT ; 
 int EBUSY ; 
 int EINVAL ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  printk (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int stub2 (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_dio_insn_bits(struct comedi_device *dev,
			    struct comedi_subdevice *s,
			    struct comedi_insn *insn, unsigned int *data)
{
#ifdef DEBUG_DIO
	printk("ni_dio_insn_bits() mask=0x%x bits=0x%x\n", data[0], data[1]);
#endif
	if (insn->n != 2)
		return -EINVAL;
	if (data[0]) {
		/* Perform check to make sure we're not using the
		   serial part of the dio */
		if ((data[0] & (DIO_SDIN | DIO_SDOUT))
		    && devpriv->serial_interval_ns)
			return -EBUSY;

		s->state &= ~data[0];
		s->state |= (data[0] & data[1]);
		devpriv->dio_output &= ~DIO_Parallel_Data_Mask;
		devpriv->dio_output |= DIO_Parallel_Data_Out(s->state);
		devpriv->stc_writew(dev, devpriv->dio_output,
				    DIO_Output_Register);
	}
	data[1] = devpriv->stc_readw(dev, DIO_Parallel_Input_Register);

	return 2;
}