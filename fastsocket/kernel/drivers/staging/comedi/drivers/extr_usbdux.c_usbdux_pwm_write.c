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
struct usbduxsub {int dummy; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {struct usbduxsub* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_CHAN (int /*<<< orphan*/ ) ; 
 int EFAULT ; 
 int EINVAL ; 
 int usbdux_pwm_pattern (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbdux_pwm_write(struct comedi_device *dev,
			    struct comedi_subdevice *s,
			    struct comedi_insn *insn, unsigned int *data)
{
	struct usbduxsub *this_usbduxsub = dev->private;

	if (!this_usbduxsub)
		return -EFAULT;

	if ((insn->n) != 1) {
		/*
		 * doesn't make sense to have more than one value here because
		 * it would just overwrite the PWM buffer a couple of times
		 */
		return -EINVAL;
	}

	/*
	 * the sign is set via a special INSN only, this gives us 8 bits for
	 * normal operation
	 * relay sign 0 by default
	 */
	return usbdux_pwm_pattern(dev, s, CR_CHAN(insn->chanspec), data[0], 0);
}