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
struct usbduxsub {int sizePwmBuf; TYPE_1__* urbPwm; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct usbduxsub* private; } ;
struct TYPE_2__ {scalar_t__ transfer_buffer; } ;

/* Variables and functions */
 int EFAULT ; 

__attribute__((used)) static int usbdux_pwm_pattern(struct comedi_device *dev,
			      struct comedi_subdevice *s, int channel,
			      unsigned int value, unsigned int sign)
{
	struct usbduxsub *this_usbduxsub = dev->private;
	int i, szbuf;
	char *pBuf;
	char pwm_mask;
	char sgn_mask;
	char c;

	if (!this_usbduxsub)
		return -EFAULT;

	/* this is the DIO bit which carries the PWM data */
	pwm_mask = (1 << channel);
	/* this is the DIO bit which carries the optional direction bit */
	sgn_mask = (16 << channel);
	/* this is the buffer which will be filled with the with bit */
	/* pattern for one period */
	szbuf = this_usbduxsub->sizePwmBuf;
	pBuf = (char *)(this_usbduxsub->urbPwm->transfer_buffer);
	for (i = 0; i < szbuf; i++) {
		c = *pBuf;
		/* reset bits */
		c = c & (~pwm_mask);
		/* set the bit as long as the index is lower than the value */
		if (i < value)
			c = c | pwm_mask;
		/* set the optional sign bit for a relay */
		if (!sign) {
			/* positive value */
			c = c & (~sgn_mask);
		} else {
			/* negative value */
			c = c | sgn_mask;
		}
		*(pBuf++) = c;
	}
	return 1;
}