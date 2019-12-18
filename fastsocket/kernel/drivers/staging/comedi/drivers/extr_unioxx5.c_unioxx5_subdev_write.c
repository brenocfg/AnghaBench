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
struct unioxx5_subd_priv {int* usp_module_type; } ;
struct comedi_subdevice {struct unioxx5_subd_priv* private; } ;
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int /*<<< orphan*/  minor; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int MODULE_DIGITAL ; 
 int /*<<< orphan*/  __unioxx5_analog_write (struct unioxx5_subd_priv*,unsigned int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __unioxx5_digital_write (struct unioxx5_subd_priv*,unsigned int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unioxx5_subdev_write(struct comedi_device *dev,
				struct comedi_subdevice *subdev,
				struct comedi_insn *insn, unsigned int *data)
{
	struct unioxx5_subd_priv *usp = subdev->private;
	int channel, type;

	channel = CR_CHAN(insn->chanspec);
	type = usp->usp_module_type[channel / 2];	/* defining module type(analog or digital) */

	if (type == MODULE_DIGITAL) {
		if (!__unioxx5_digital_write(usp, data, channel, dev->minor))
			return -1;
	} else {
		if (!__unioxx5_analog_write(usp, data, channel, dev->minor))
			return -1;
	}

	return 1;
}