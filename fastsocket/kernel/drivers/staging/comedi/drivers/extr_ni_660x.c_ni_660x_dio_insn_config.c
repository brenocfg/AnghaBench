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
typedef  int uint64_t ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int pfi_direction_bits; int /*<<< orphan*/ * pfi_output_selects; } ;

/* Variables and functions */
 unsigned int COMEDI_INPUT ; 
 unsigned int COMEDI_OUTPUT ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  INSN_CONFIG_DIO_INPUT 133 
#define  INSN_CONFIG_DIO_OUTPUT 132 
#define  INSN_CONFIG_DIO_QUERY 131 
#define  INSN_CONFIG_FILTER 130 
#define  INSN_CONFIG_GET_ROUTING 129 
#define  INSN_CONFIG_SET_ROUTING 128 
 int /*<<< orphan*/  ni660x_config_filter (struct comedi_device*,int,unsigned int) ; 
 unsigned int ni_660x_get_pfi_routing (struct comedi_device*,int) ; 
 int /*<<< orphan*/  ni_660x_select_pfi_output (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int ni_660x_set_pfi_routing (struct comedi_device*,int,unsigned int) ; 
 int /*<<< orphan*/  pfi_output_select_high_Z ; 
 TYPE_1__* private (struct comedi_device*) ; 

__attribute__((used)) static int ni_660x_dio_insn_config(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn, unsigned int *data)
{
	int chan = CR_CHAN(insn->chanspec);

	/* The input or output configuration of each digital line is
	 * configured by a special insn_config instruction.  chanspec
	 * contains the channel to be changed, and data[0] contains the
	 * value COMEDI_INPUT or COMEDI_OUTPUT. */

	switch (data[0]) {
	case INSN_CONFIG_DIO_OUTPUT:
		private(dev)->pfi_direction_bits |= ((uint64_t) 1) << chan;
		ni_660x_select_pfi_output(dev, chan,
					  private(dev)->
					  pfi_output_selects[chan]);
		break;
	case INSN_CONFIG_DIO_INPUT:
		private(dev)->pfi_direction_bits &= ~(((uint64_t) 1) << chan);
		ni_660x_select_pfi_output(dev, chan, pfi_output_select_high_Z);
		break;
	case INSN_CONFIG_DIO_QUERY:
		data[1] =
		    (private(dev)->pfi_direction_bits &
		     (((uint64_t) 1) << chan)) ? COMEDI_OUTPUT : COMEDI_INPUT;
		return 0;
	case INSN_CONFIG_SET_ROUTING:
		return ni_660x_set_pfi_routing(dev, chan, data[1]);
		break;
	case INSN_CONFIG_GET_ROUTING:
		data[1] = ni_660x_get_pfi_routing(dev, chan);
		break;
	case INSN_CONFIG_FILTER:
		ni660x_config_filter(dev, chan, data[1]);
		break;
	default:
		return -EINVAL;
		break;
	};
	return 0;
}