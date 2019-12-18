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
struct ni_gpct {int /*<<< orphan*/  counter_index; } ;
struct comedi_subdevice {int /*<<< orphan*/  async; struct ni_gpct* private; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_INPUT ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  ni_e_series_enable_second_irq (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 int ni_request_gpct_mite_channel (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_tio_acknowledge_and_confirm (struct ni_gpct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ni_tio_cmd (struct ni_gpct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_gpct_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	int retval;
#ifdef PCIDMA
	struct ni_gpct *counter = s->private;
/* const struct comedi_cmd *cmd = &s->async->cmd; */

	retval = ni_request_gpct_mite_channel(dev, counter->counter_index,
					      COMEDI_INPUT);
	if (retval) {
		comedi_error(dev,
			     "no dma channel available for use by counter");
		return retval;
	}
	ni_tio_acknowledge_and_confirm(counter, NULL, NULL, NULL, NULL);
	ni_e_series_enable_second_irq(dev, counter->counter_index, 1);
	retval = ni_tio_cmd(counter, s->async);
#else
	retval = -ENOTSUPP;
#endif
	return retval;
}