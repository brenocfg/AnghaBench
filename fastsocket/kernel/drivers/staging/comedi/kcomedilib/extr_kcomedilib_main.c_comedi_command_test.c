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
struct comedi_subdevice {scalar_t__ type; int (* do_cmdtest ) (struct comedi_device*,struct comedi_subdevice*,struct comedi_cmd*) ;int /*<<< orphan*/ * async; } ;
struct comedi_device {scalar_t__ n_subdevices; struct comedi_subdevice* subdevices; } ;
struct comedi_cmd {scalar_t__ subdev; } ;

/* Variables and functions */
 scalar_t__ COMEDI_SUBD_UNUSED ; 
 int EIO ; 
 int ENODEV ; 
 int stub1 (struct comedi_device*,struct comedi_subdevice*,struct comedi_cmd*) ; 

int comedi_command_test(void *d, struct comedi_cmd *cmd)
{
	struct comedi_device *dev = (struct comedi_device *)d;
	struct comedi_subdevice *s;

	if (cmd->subdev >= dev->n_subdevices)
		return -ENODEV;

	s = dev->subdevices + cmd->subdev;
	if (s->type == COMEDI_SUBD_UNUSED)
		return -EIO;

	if (s->async == NULL)
		return -ENODEV;

	return s->do_cmdtest(dev, s, cmd);
}