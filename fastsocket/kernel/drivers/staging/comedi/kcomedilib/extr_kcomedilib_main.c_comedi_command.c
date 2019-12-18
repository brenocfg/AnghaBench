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
struct comedi_subdevice {scalar_t__ type; int (* do_cmd ) (struct comedi_device*,struct comedi_subdevice*) ;void* busy; struct comedi_async* async; } ;
struct comedi_device {scalar_t__ n_subdevices; struct comedi_subdevice* subdevices; } ;
struct comedi_cmd {scalar_t__ subdev; int /*<<< orphan*/  flags; } ;
struct comedi_async {int cb_mask; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int COMEDI_CB_EOS ; 
 scalar_t__ COMEDI_SUBD_UNUSED ; 
 int EBUSY ; 
 int EIO ; 
 int ENODEV ; 
 unsigned int SRF_RUNNING ; 
 int /*<<< orphan*/  TRIG_WAKE_EOS ; 
 int /*<<< orphan*/  comedi_reset_async_buf (struct comedi_async*) ; 
 int /*<<< orphan*/  comedi_set_subdevice_runflags (struct comedi_subdevice*,int /*<<< orphan*/ ,unsigned int) ; 
 int stub1 (struct comedi_device*,struct comedi_subdevice*) ; 

int comedi_command(void *d, struct comedi_cmd *cmd)
{
	struct comedi_device *dev = (struct comedi_device *)d;
	struct comedi_subdevice *s;
	struct comedi_async *async;
	unsigned runflags;

	if (cmd->subdev >= dev->n_subdevices)
		return -ENODEV;

	s = dev->subdevices + cmd->subdev;
	if (s->type == COMEDI_SUBD_UNUSED)
		return -EIO;

	async = s->async;
	if (async == NULL)
		return -ENODEV;

	if (s->busy)
		return -EBUSY;
	s->busy = d;

	if (async->cb_mask & COMEDI_CB_EOS)
		cmd->flags |= TRIG_WAKE_EOS;

	async->cmd = *cmd;

	runflags = SRF_RUNNING;

	comedi_set_subdevice_runflags(s, ~0, runflags);

	comedi_reset_async_buf(async);

	return s->do_cmd(dev, s);
}