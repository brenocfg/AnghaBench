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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_6__ {int ao_fifo_depth; } ;
struct TYPE_5__ {TYPE_1__* mite; } ;
struct TYPE_4__ {unsigned int fifo_size; } ;

/* Variables and functions */
#define  COMEDI_INPUT 130 
#define  COMEDI_OUTPUT 129 
 int EINVAL ; 
#define  INSN_CONFIG_GET_HARDWARE_BUFFER_SIZE 128 
 TYPE_3__ boardtype ; 
 TYPE_2__* devpriv ; 

__attribute__((used)) static int ni_ao_insn_config(struct comedi_device *dev,
			     struct comedi_subdevice *s,
			     struct comedi_insn *insn, unsigned int *data)
{
	switch (data[0]) {
	case INSN_CONFIG_GET_HARDWARE_BUFFER_SIZE:
		switch (data[1]) {
		case COMEDI_OUTPUT:
			data[2] = 1 + boardtype.ao_fifo_depth * sizeof(short);
			if (devpriv->mite)
				data[2] += devpriv->mite->fifo_size;
			break;
		case COMEDI_INPUT:
			data[2] = 0;
			break;
		default:
			return -EINVAL;
			break;
		}
		return 0;
	default:
		break;
	}

	return -EINVAL;
}