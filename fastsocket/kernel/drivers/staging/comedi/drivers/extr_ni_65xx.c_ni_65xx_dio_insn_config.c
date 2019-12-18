#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int /*<<< orphan*/  type; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_6__ {unsigned int* dio_direction; TYPE_1__* mite; } ;
struct TYPE_5__ {unsigned int base_port; } ;
struct TYPE_4__ {scalar_t__ daq_io_addr; } ;

/* Variables and functions */
 unsigned int COMEDI_INPUT ; 
 unsigned int COMEDI_OUTPUT ; 
 int /*<<< orphan*/  COMEDI_SUBD_DIO ; 
 int /*<<< orphan*/  CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  INSN_CONFIG_DIO_INPUT 131 
#define  INSN_CONFIG_DIO_OUTPUT 130 
#define  INSN_CONFIG_DIO_QUERY 129 
#define  INSN_CONFIG_FILTER 128 
 scalar_t__ Port_Select (unsigned int) ; 
 int ni_65xx_config_filter (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ; 
 unsigned int ni_65xx_port_by_channel (int /*<<< orphan*/ ) ; 
 TYPE_3__* private (struct comedi_device*) ; 
 TYPE_2__* sprivate (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int ni_65xx_dio_insn_config(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn, unsigned int *data)
{
	unsigned port;

	if (insn->n < 1)
		return -EINVAL;
	port = sprivate(s)->base_port +
	    ni_65xx_port_by_channel(CR_CHAN(insn->chanspec));
	switch (data[0]) {
	case INSN_CONFIG_FILTER:
		return ni_65xx_config_filter(dev, s, insn, data);
		break;
	case INSN_CONFIG_DIO_OUTPUT:
		if (s->type != COMEDI_SUBD_DIO)
			return -EINVAL;
		private(dev)->dio_direction[port] = COMEDI_OUTPUT;
		writeb(0, private(dev)->mite->daq_io_addr + Port_Select(port));
		return 1;
		break;
	case INSN_CONFIG_DIO_INPUT:
		if (s->type != COMEDI_SUBD_DIO)
			return -EINVAL;
		private(dev)->dio_direction[port] = COMEDI_INPUT;
		writeb(1, private(dev)->mite->daq_io_addr + Port_Select(port));
		return 1;
		break;
	case INSN_CONFIG_DIO_QUERY:
		if (s->type != COMEDI_SUBD_DIO)
			return -EINVAL;
		data[1] = private(dev)->dio_direction[port];
		return insn->n;
		break;
	default:
		break;
	}
	return -EINVAL;
}