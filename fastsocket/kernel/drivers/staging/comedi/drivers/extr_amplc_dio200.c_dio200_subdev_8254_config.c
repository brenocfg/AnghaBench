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
struct dio200_subdev_8254 {int /*<<< orphan*/  iobase; } ;
struct comedi_subdevice {struct dio200_subdev_8254* private; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  INSN_CONFIG_8254_READ_STATUS 133 
#define  INSN_CONFIG_GET_CLOCK_SRC 132 
#define  INSN_CONFIG_GET_GATE_SRC 131 
#define  INSN_CONFIG_SET_CLOCK_SRC 130 
#define  INSN_CONFIG_SET_COUNTER_MODE 129 
#define  INSN_CONFIG_SET_GATE_SRC 128 
 int dio200_get_clock_src (struct dio200_subdev_8254*,int,unsigned int*) ; 
 int dio200_get_gate_src (struct dio200_subdev_8254*,int) ; 
 int dio200_set_clock_src (struct dio200_subdev_8254*,int,unsigned int) ; 
 int dio200_set_gate_src (struct dio200_subdev_8254*,int,unsigned int) ; 
 int i8254_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 unsigned int i8254_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
dio200_subdev_8254_config(struct comedi_device *dev, struct comedi_subdevice *s,
			  struct comedi_insn *insn, unsigned int *data)
{
	struct dio200_subdev_8254 *subpriv = s->private;
	int ret;
	int chan = CR_CHAN(insn->chanspec);

	switch (data[0]) {
	case INSN_CONFIG_SET_COUNTER_MODE:
		ret = i8254_set_mode(subpriv->iobase, 0, chan, data[1]);
		if (ret < 0)
			return -EINVAL;
		break;
	case INSN_CONFIG_8254_READ_STATUS:
		data[1] = i8254_status(subpriv->iobase, 0, chan);
		break;
	case INSN_CONFIG_SET_GATE_SRC:
		ret = dio200_set_gate_src(subpriv, chan, data[2]);
		if (ret < 0)
			return -EINVAL;
		break;
	case INSN_CONFIG_GET_GATE_SRC:
		ret = dio200_get_gate_src(subpriv, chan);
		if (ret < 0)
			return -EINVAL;
		data[2] = ret;
		break;
	case INSN_CONFIG_SET_CLOCK_SRC:
		ret = dio200_set_clock_src(subpriv, chan, data[1]);
		if (ret < 0)
			return -EINVAL;
		break;
	case INSN_CONFIG_GET_CLOCK_SRC:
		ret = dio200_get_clock_src(subpriv, chan, &data[2]);
		if (ret < 0)
			return -EINVAL;
		data[1] = ret;
		break;
	default:
		return -EINVAL;
		break;
	}
	return insn->n;
}