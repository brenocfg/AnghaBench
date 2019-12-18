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
struct TYPE_2__ {int /*<<< orphan*/  WRDOut; } ;

/* Variables and functions */
#define  COMEDI_INPUT 130 
#define  COMEDI_OUTPUT 129 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBIwrite (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
#define  INSN_CONFIG_DIO_QUERY 128 
 TYPE_1__* diopriv ; 

__attribute__((used)) static int s626_dio_insn_config(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn, unsigned int *data)
{

	switch (data[0]) {
	case INSN_CONFIG_DIO_QUERY:
		data[1] =
		    (s->
		     io_bits & (1 << CR_CHAN(insn->chanspec))) ? COMEDI_OUTPUT :
		    COMEDI_INPUT;
		return insn->n;
		break;
	case COMEDI_INPUT:
		s->io_bits &= ~(1 << CR_CHAN(insn->chanspec));
		break;
	case COMEDI_OUTPUT:
		s->io_bits |= 1 << CR_CHAN(insn->chanspec);
		break;
	default:
		return -EINVAL;
		break;
	}
	DEBIwrite(dev, diopriv->WRDOut, s->io_bits);

	return 1;
}