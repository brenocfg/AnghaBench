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
struct comedi_subdevice {int io_bits; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dio_control; int /*<<< orphan*/  (* stc_writew ) (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 unsigned int COMEDI_INPUT ; 
 unsigned int COMEDI_OUTPUT ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIO_Control_Register ; 
 int /*<<< orphan*/  DIO_Pins_Dir (int) ; 
 int /*<<< orphan*/  DIO_Pins_Dir_Mask ; 
 int EINVAL ; 
#define  INSN_CONFIG_DIO_INPUT 130 
#define  INSN_CONFIG_DIO_OUTPUT 129 
#define  INSN_CONFIG_DIO_QUERY 128 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  printk (char*,int,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_dio_insn_config(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn, unsigned int *data)
{
#ifdef DEBUG_DIO
	printk("ni_dio_insn_config() chan=%d io=%d\n",
	       CR_CHAN(insn->chanspec), data[0]);
#endif
	switch (data[0]) {
	case INSN_CONFIG_DIO_OUTPUT:
		s->io_bits |= 1 << CR_CHAN(insn->chanspec);
		break;
	case INSN_CONFIG_DIO_INPUT:
		s->io_bits &= ~(1 << CR_CHAN(insn->chanspec));
		break;
	case INSN_CONFIG_DIO_QUERY:
		data[1] =
		    (s->
		     io_bits & (1 << CR_CHAN(insn->chanspec))) ? COMEDI_OUTPUT :
		    COMEDI_INPUT;
		return insn->n;
		break;
	default:
		return -EINVAL;
	}

	devpriv->dio_control &= ~DIO_Pins_Dir_Mask;
	devpriv->dio_control |= DIO_Pins_Dir(s->io_bits);
	devpriv->stc_writew(dev, devpriv->dio_control, DIO_Control_Register);

	return 1;
}