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
struct usbduxsub {TYPE_1__* interface; int /*<<< orphan*/  probed; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  minor; struct usbduxsub* private; } ;
struct comedi_cmd {int start_src; int scan_begin_src; int convert_src; int scan_end_src; int stop_src; scalar_t__ start_arg; int scan_begin_arg; int convert_arg; scalar_t__ scan_end_arg; scalar_t__ chanlist_len; scalar_t__ stop_arg; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENODEV ; 
 int TRIG_COUNT ; 
 int TRIG_EXT ; 
 int TRIG_FOLLOW ; 
 int TRIG_INT ; 
 int TRIG_NONE ; 
 int TRIG_NOW ; 
 int TRIG_TIMER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int usbdux_ao_cmdtest(struct comedi_device *dev,
			     struct comedi_subdevice *s, struct comedi_cmd *cmd)
{
	int err = 0, tmp;
	struct usbduxsub *this_usbduxsub = dev->private;

	if (!this_usbduxsub)
		return -EFAULT;

	if (!(this_usbduxsub->probed))
		return -ENODEV;

	dev_dbg(&this_usbduxsub->interface->dev,
		"comedi%d: usbdux_ao_cmdtest\n", dev->minor);

	/* make sure triggers are valid */
	/* Only immediate triggers are allowed */
	tmp = cmd->start_src;
	cmd->start_src &= TRIG_NOW | TRIG_INT;
	if (!cmd->start_src || tmp != cmd->start_src)
		err++;

	/* trigger should happen timed */
	tmp = cmd->scan_begin_src;
	/* just now we scan also in the high speed mode every frame */
	/* this is due to ehci driver limitations */
	if (0) {		/* (this_usbduxsub->high_speed) */
		/* start immidiately a new scan */
		/* the sampling rate is set by the coversion rate */
		cmd->scan_begin_src &= TRIG_FOLLOW;
	} else {
		/* start a new scan (output at once) with a timer */
		cmd->scan_begin_src &= TRIG_TIMER;
	}
	if (!cmd->scan_begin_src || tmp != cmd->scan_begin_src)
		err++;

	/* scanning is continous */
	tmp = cmd->convert_src;
	/* we always output at 1kHz just now all channels at once */
	if (0) {		/* (this_usbduxsub->high_speed) */
		/*
		 * in usb-2.0 only one conversion it tranmitted but with 8kHz/n
		 */
		cmd->convert_src &= TRIG_TIMER;
	} else {
		/* all conversion events happen simultaneously with a rate of
		 * 1kHz/n */
		cmd->convert_src &= TRIG_NOW;
	}
	if (!cmd->convert_src || tmp != cmd->convert_src)
		err++;

	/* issue a trigger when scan is finished and start a new scan */
	tmp = cmd->scan_end_src;
	cmd->scan_end_src &= TRIG_COUNT;
	if (!cmd->scan_end_src || tmp != cmd->scan_end_src)
		err++;

	/* trigger at the end of count events or not, stop condition or not */
	tmp = cmd->stop_src;
	cmd->stop_src &= TRIG_COUNT | TRIG_NONE;
	if (!cmd->stop_src || tmp != cmd->stop_src)
		err++;

	if (err)
		return 1;

	/*
	 * step 2: make sure trigger sources are unique and mutually compatible
	 * note that mutual compatiblity is not an issue here
	 */
	if (cmd->scan_begin_src != TRIG_FOLLOW &&
	    cmd->scan_begin_src != TRIG_EXT &&
	    cmd->scan_begin_src != TRIG_TIMER)
		err++;
	if (cmd->stop_src != TRIG_COUNT && cmd->stop_src != TRIG_NONE)
		err++;

	if (err)
		return 2;

	/* step 3: make sure arguments are trivially compatible */

	if (cmd->start_arg != 0) {
		cmd->start_arg = 0;
		err++;
	}

	if (cmd->scan_begin_src == TRIG_FOLLOW) {
		/* internal trigger */
		if (cmd->scan_begin_arg != 0) {
			cmd->scan_begin_arg = 0;
			err++;
		}
	}

	if (cmd->scan_begin_src == TRIG_TIMER) {
		/* timer */
		if (cmd->scan_begin_arg < 1000000) {
			cmd->scan_begin_arg = 1000000;
			err++;
		}
	}
	/* not used now, is for later use */
	if (cmd->convert_src == TRIG_TIMER) {
		if (cmd->convert_arg < 125000) {
			cmd->convert_arg = 125000;
			err++;
		}
	}

	/* the same argument */
	if (cmd->scan_end_arg != cmd->chanlist_len) {
		cmd->scan_end_arg = cmd->chanlist_len;
		err++;
	}

	if (cmd->stop_src == TRIG_COUNT) {
		/* any count is allowed */
	} else {
		/* TRIG_NONE */
		if (cmd->stop_arg != 0) {
			cmd->stop_arg = 0;
			err++;
		}
	}

	dev_dbg(&this_usbduxsub->interface->dev, "comedi%d: err=%d, "
		"scan_begin_src=%d, scan_begin_arg=%d, convert_src=%d, "
		"convert_arg=%d\n", dev->minor, err, cmd->scan_begin_src,
		cmd->scan_begin_arg, cmd->convert_src, cmd->convert_arg);

	if (err)
		return 3;

	return 0;
}