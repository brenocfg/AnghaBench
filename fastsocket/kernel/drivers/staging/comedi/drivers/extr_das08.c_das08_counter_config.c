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
struct comedi_insn {int chanspec; int n; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i8254; } ;

/* Variables and functions */
 int EINVAL ; 
#define  INSN_CONFIG_8254_READ_STATUS 129 
#define  INSN_CONFIG_SET_COUNTER_MODE 128 
 TYPE_1__* devpriv ; 
 unsigned int i8254_read_status (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i8254_set_mode (int /*<<< orphan*/ *,int,unsigned int) ; 

__attribute__((used)) static int das08_counter_config(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn, unsigned int *data)
{
	int chan = insn->chanspec;

	if (insn->n != 2)
		return -EINVAL;

	switch (data[0]) {
	case INSN_CONFIG_SET_COUNTER_MODE:
		i8254_set_mode(&devpriv->i8254, chan, data[1]);
		break;
	case INSN_CONFIG_8254_READ_STATUS:
		data[1] = i8254_read_status(&devpriv->i8254, chan);
		break;
	default:
		return -EINVAL;
		break;
	}
	return 2;
}