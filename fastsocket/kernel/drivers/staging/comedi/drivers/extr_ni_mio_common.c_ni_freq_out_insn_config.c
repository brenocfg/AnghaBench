#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int dummy; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  INSN_CONFIG_GET_CLOCK_SRC 129 
#define  INSN_CONFIG_SET_CLOCK_SRC 128 
 int /*<<< orphan*/  ni_get_freq_out_clock (struct comedi_device*,unsigned int*,unsigned int*) ; 
 int ni_set_freq_out_clock (struct comedi_device*,unsigned int) ; 

__attribute__((used)) static int ni_freq_out_insn_config(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn, unsigned int *data)
{
	switch (data[0]) {
	case INSN_CONFIG_SET_CLOCK_SRC:
		return ni_set_freq_out_clock(dev, data[1]);
		break;
	case INSN_CONFIG_GET_CLOCK_SRC:
		ni_get_freq_out_clock(dev, &data[1], &data[2]);
		return 3;
	default:
		break;
	}
	return -EINVAL;
}