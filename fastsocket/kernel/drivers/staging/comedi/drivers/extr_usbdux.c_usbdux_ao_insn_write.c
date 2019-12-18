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
struct usbduxsub {int* dux_commands; unsigned int* outBuffer; int /*<<< orphan*/  sem; TYPE_1__* interface; scalar_t__ ao_cmd_running; int /*<<< orphan*/  probed; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int /*<<< orphan*/  minor; struct usbduxsub* private; } ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EFAULT ; 
 int ENODEV ; 
 int /*<<< orphan*/  SENDDACOMMANDS ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int send_dux_commands (struct usbduxsub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usbdux_ao_insn_write(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn, unsigned int *data)
{
	int i, err;
	int chan = CR_CHAN(insn->chanspec);
	struct usbduxsub *this_usbduxsub = dev->private;

	if (!this_usbduxsub)
		return -EFAULT;

	dev_dbg(&this_usbduxsub->interface->dev,
		"comedi%d: ao_insn_write\n", dev->minor);

	down(&this_usbduxsub->sem);
	if (!(this_usbduxsub->probed)) {
		up(&this_usbduxsub->sem);
		return -ENODEV;
	}
	if (this_usbduxsub->ao_cmd_running) {
		dev_err(&this_usbduxsub->interface->dev,
			"comedi%d: ao_insn_write: "
			"ERROR: asynchronous ao_cmd is running\n", dev->minor);
		up(&this_usbduxsub->sem);
		return 0;
	}

	for (i = 0; i < insn->n; i++) {
		dev_dbg(&this_usbduxsub->interface->dev,
			"comedi%d: ao_insn_write: data[chan=%d,i=%d]=%d\n",
			dev->minor, chan, i, data[i]);

		/* number of channels: 1 */
		this_usbduxsub->dux_commands[1] = 1;
		/* one 16 bit value */
		*((int16_t *) (this_usbduxsub->dux_commands + 2)) =
		    cpu_to_le16(data[i]);
		this_usbduxsub->outBuffer[chan] = data[i];
		/* channel number */
		this_usbduxsub->dux_commands[4] = (chan << 6);
		err = send_dux_commands(this_usbduxsub, SENDDACOMMANDS);
		if (err < 0) {
			up(&this_usbduxsub->sem);
			return err;
		}
	}
	up(&this_usbduxsub->sem);

	return i;
}