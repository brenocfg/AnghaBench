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
struct usbduxsub {int ai_cmd_running; int* dux_commands; int ai_interval; int ai_timer; int ai_counter; int ai_continous; int /*<<< orphan*/  sem; scalar_t__ ai_sample_count; TYPE_1__* interface; scalar_t__ high_speed; int /*<<< orphan*/  probed; } ;
struct comedi_subdevice {TYPE_2__* async; } ;
struct comedi_device {int /*<<< orphan*/  minor; struct usbduxsub* private; } ;
struct comedi_cmd {int chanlist_len; int scan_begin_arg; scalar_t__ stop_src; scalar_t__ start_src; scalar_t__ stop_arg; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_4__ {int /*<<< orphan*/ * inttrig; scalar_t__ cur_chan; struct comedi_cmd cmd; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 int NUMCHANNELS ; 
 int /*<<< orphan*/  SENDADCOMMANDS ; 
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ TRIG_NOW ; 
 int create_adc_command (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int send_dux_commands (struct usbduxsub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * usbdux_ai_inttrig ; 
 int usbduxsub_submit_InURBs (struct usbduxsub*) ; 

__attribute__((used)) static int usbdux_ai_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int chan, range;
	int i, ret;
	struct usbduxsub *this_usbduxsub = dev->private;
	int result;

	if (!this_usbduxsub)
		return -EFAULT;

	dev_dbg(&this_usbduxsub->interface->dev,
		"comedi%d: usbdux_ai_cmd\n", dev->minor);

	/* block other CPUs from starting an ai_cmd */
	down(&this_usbduxsub->sem);

	if (!(this_usbduxsub->probed)) {
		up(&this_usbduxsub->sem);
		return -ENODEV;
	}
	if (this_usbduxsub->ai_cmd_running) {
		dev_err(&this_usbduxsub->interface->dev, "comedi%d: "
			"ai_cmd not possible. Another ai_cmd is running.\n",
			dev->minor);
		up(&this_usbduxsub->sem);
		return -EBUSY;
	}
	/* set current channel of the running aquisition to zero */
	s->async->cur_chan = 0;

	this_usbduxsub->dux_commands[1] = cmd->chanlist_len;
	for (i = 0; i < cmd->chanlist_len; ++i) {
		chan = CR_CHAN(cmd->chanlist[i]);
		range = CR_RANGE(cmd->chanlist[i]);
		if (i >= NUMCHANNELS) {
			dev_err(&this_usbduxsub->interface->dev,
				"comedi%d: channel list too long\n",
				dev->minor);
			break;
		}
		this_usbduxsub->dux_commands[i + 2] =
		    create_adc_command(chan, range);
	}

	dev_dbg(&this_usbduxsub->interface->dev,
		"comedi %d: sending commands to the usb device: size=%u\n",
		dev->minor, NUMCHANNELS);

	result = send_dux_commands(this_usbduxsub, SENDADCOMMANDS);
	if (result < 0) {
		up(&this_usbduxsub->sem);
		return result;
	}

	if (this_usbduxsub->high_speed) {
		/*
		 * every channel gets a time window of 125us. Thus, if we
		 * sample all 8 channels we need 1ms. If we sample only one
		 * channel we need only 125us
		 */
		this_usbduxsub->ai_interval = 1;
		/* find a power of 2 for the interval */
		while ((this_usbduxsub->ai_interval) < (cmd->chanlist_len)) {
			this_usbduxsub->ai_interval =
			    (this_usbduxsub->ai_interval) * 2;
		}
		this_usbduxsub->ai_timer = cmd->scan_begin_arg / (125000 *
								  (this_usbduxsub->
								   ai_interval));
	} else {
		/* interval always 1ms */
		this_usbduxsub->ai_interval = 1;
		this_usbduxsub->ai_timer = cmd->scan_begin_arg / 1000000;
	}
	if (this_usbduxsub->ai_timer < 1) {
		dev_err(&this_usbduxsub->interface->dev, "comedi%d: ai_cmd: "
			"timer=%d, scan_begin_arg=%d. "
			"Not properly tested by cmdtest?\n", dev->minor,
			this_usbduxsub->ai_timer, cmd->scan_begin_arg);
		up(&this_usbduxsub->sem);
		return -EINVAL;
	}
	this_usbduxsub->ai_counter = this_usbduxsub->ai_timer;

	if (cmd->stop_src == TRIG_COUNT) {
		/* data arrives as one packet */
		this_usbduxsub->ai_sample_count = cmd->stop_arg;
		this_usbduxsub->ai_continous = 0;
	} else {
		/* continous aquisition */
		this_usbduxsub->ai_continous = 1;
		this_usbduxsub->ai_sample_count = 0;
	}

	if (cmd->start_src == TRIG_NOW) {
		/* enable this acquisition operation */
		this_usbduxsub->ai_cmd_running = 1;
		ret = usbduxsub_submit_InURBs(this_usbduxsub);
		if (ret < 0) {
			this_usbduxsub->ai_cmd_running = 0;
			/* fixme: unlink here?? */
			up(&this_usbduxsub->sem);
			return ret;
		}
		s->async->inttrig = NULL;
	} else {
		/* TRIG_INT */
		/* don't enable the acquision operation */
		/* wait for an internal signal */
		s->async->inttrig = usbdux_ai_inttrig;
	}
	up(&this_usbduxsub->sem);
	return 0;
}