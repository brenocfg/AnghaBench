#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {unsigned int n_adchan; int /*<<< orphan*/  has_analog_trig; } ;
struct TYPE_3__ {unsigned int atrig_low; unsigned int atrig_high; int atrig_mode; } ;

/* Variables and functions */
 unsigned int COMEDI_EV_SCAN_BEGIN ; 
 int EAGAIN ; 
 int EINVAL ; 
 TYPE_2__ boardtype ; 
 TYPE_1__* devpriv ; 

__attribute__((used)) static int ni_ai_config_analog_trig(struct comedi_device *dev,
				    struct comedi_subdevice *s,
				    struct comedi_insn *insn,
				    unsigned int *data)
{
	unsigned int a, b, modebits;
	int err = 0;

	/* data[1] is flags
	 * data[2] is analog line
	 * data[3] is set level
	 * data[4] is reset level */
	if (!boardtype.has_analog_trig)
		return -EINVAL;
	if ((data[1] & 0xffff0000) != COMEDI_EV_SCAN_BEGIN) {
		data[1] &= (COMEDI_EV_SCAN_BEGIN | 0xffff);
		err++;
	}
	if (data[2] >= boardtype.n_adchan) {
		data[2] = boardtype.n_adchan - 1;
		err++;
	}
	if (data[3] > 255) {	/* a */
		data[3] = 255;
		err++;
	}
	if (data[4] > 255) {	/* b */
		data[4] = 255;
		err++;
	}
	/*
	 * 00 ignore
	 * 01 set
	 * 10 reset
	 *
	 * modes:
	 *   1 level:                    +b-   +a-
	 *     high mode                00 00 01 10
	 *     low mode                 00 00 10 01
	 *   2 level: (a<b)
	 *     hysteresis low mode      10 00 00 01
	 *     hysteresis high mode     01 00 00 10
	 *     middle mode              10 01 01 10
	 */

	a = data[3];
	b = data[4];
	modebits = data[1] & 0xff;
	if (modebits & 0xf0) {
		/* two level mode */
		if (b < a) {
			/* swap order */
			a = data[4];
			b = data[3];
			modebits =
			    ((data[1] & 0xf) << 4) | ((data[1] & 0xf0) >> 4);
		}
		devpriv->atrig_low = a;
		devpriv->atrig_high = b;
		switch (modebits) {
		case 0x81:	/* low hysteresis mode */
			devpriv->atrig_mode = 6;
			break;
		case 0x42:	/* high hysteresis mode */
			devpriv->atrig_mode = 3;
			break;
		case 0x96:	/* middle window mode */
			devpriv->atrig_mode = 2;
			break;
		default:
			data[1] &= ~0xff;
			err++;
		}
	} else {
		/* one level mode */
		if (b != 0) {
			data[4] = 0;
			err++;
		}
		switch (modebits) {
		case 0x06:	/* high window mode */
			devpriv->atrig_high = a;
			devpriv->atrig_mode = 0;
			break;
		case 0x09:	/* low window mode */
			devpriv->atrig_low = a;
			devpriv->atrig_mode = 1;
			break;
		default:
			data[1] &= ~0xff;
			err++;
		}
	}
	if (err)
		return -EAGAIN;
	return 5;
}