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
struct TYPE_2__ {int dio_config_output; } ;

/* Variables and functions */
 unsigned int COMEDI_INPUT ; 
 unsigned int COMEDI_OUTPUT ; 
 int EINVAL ; 
#define  INSN_CONFIG_BLOCK_SIZE 131 
#define  INSN_CONFIG_DIO_INPUT 130 
#define  INSN_CONFIG_DIO_OUTPUT 129 
#define  INSN_CONFIG_DIO_QUERY 128 
 int dio_config_block_size (struct comedi_device*,unsigned int*) ; 
 TYPE_1__* priv (struct comedi_device*) ; 

__attribute__((used)) static int dio_config_insn(struct comedi_device *dev,
			   struct comedi_subdevice *s, struct comedi_insn *insn,
			   unsigned int *data)
{
	switch (data[0]) {
	case INSN_CONFIG_DIO_OUTPUT:
		priv(dev)->dio_config_output = 1;
		return insn->n;
		break;
	case INSN_CONFIG_DIO_INPUT:
		priv(dev)->dio_config_output = 0;
		return insn->n;
		break;
	case INSN_CONFIG_DIO_QUERY:
		data[1] =
		    priv(dev)->dio_config_output ? COMEDI_OUTPUT : COMEDI_INPUT;
		return insn->n;
		break;
	case INSN_CONFIG_BLOCK_SIZE:
		return dio_config_block_size(dev, data);
		break;
	default:
		break;
	}

	return -EINVAL;
}