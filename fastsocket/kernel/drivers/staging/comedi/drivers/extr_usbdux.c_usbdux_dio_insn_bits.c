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
struct usbduxsub {unsigned int* dux_commands; int /*<<< orphan*/  sem; int /*<<< orphan*/ * insnBuffer; int /*<<< orphan*/  probed; } ;
struct comedi_subdevice {unsigned int state; unsigned int io_bits; } ;
struct comedi_insn {int n; } ;
struct comedi_device {struct usbduxsub* private; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  SENDDIOBITSCOMMAND ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int receive_dux_commands (struct usbduxsub*,int /*<<< orphan*/ ) ; 
 int send_dux_commands (struct usbduxsub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usbdux_dio_insn_bits(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn, unsigned int *data)
{

	struct usbduxsub *this_usbduxsub = dev->private;
	int err;

	if (!this_usbduxsub)
		return -EFAULT;

	if (insn->n != 2)
		return -EINVAL;

	down(&this_usbduxsub->sem);

	if (!(this_usbduxsub->probed)) {
		up(&this_usbduxsub->sem);
		return -ENODEV;
	}

	/* The insn data is a mask in data[0] and the new data
	 * in data[1], each channel cooresponding to a bit. */
	s->state &= ~data[0];
	s->state |= data[0] & data[1];
	this_usbduxsub->dux_commands[1] = s->io_bits;
	this_usbduxsub->dux_commands[2] = s->state;

	/* This command also tells the firmware to return */
	/* the digital input lines */
	err = send_dux_commands(this_usbduxsub, SENDDIOBITSCOMMAND);
	if (err < 0) {
		up(&this_usbduxsub->sem);
		return err;
	}
	err = receive_dux_commands(this_usbduxsub, SENDDIOBITSCOMMAND);
	if (err < 0) {
		up(&this_usbduxsub->sem);
		return err;
	}

	data[1] = le16_to_cpu(this_usbduxsub->insnBuffer[1]);
	up(&this_usbduxsub->sem);
	return 2;
}