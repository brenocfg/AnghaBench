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
struct ni_gpct {int dummy; } ;
struct comedi_subdevice {int /*<<< orphan*/  async; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_INPUT ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int ni_660x_request_mite_channel (struct comedi_device*,struct ni_gpct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_tio_acknowledge_and_confirm (struct ni_gpct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ni_tio_cmd (struct ni_gpct*,int /*<<< orphan*/ ) ; 
 struct ni_gpct* subdev_to_counter (struct comedi_subdevice*) ; 

__attribute__((used)) static int ni_660x_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	int retval;

	struct ni_gpct *counter = subdev_to_counter(s);
/* const struct comedi_cmd *cmd = &s->async->cmd; */

	retval = ni_660x_request_mite_channel(dev, counter, COMEDI_INPUT);
	if (retval) {
		comedi_error(dev,
			     "no dma channel available for use by counter");
		return retval;
	}
	ni_tio_acknowledge_and_confirm(counter, NULL, NULL, NULL, NULL);
	retval = ni_tio_cmd(counter, s->async);

	return retval;
}