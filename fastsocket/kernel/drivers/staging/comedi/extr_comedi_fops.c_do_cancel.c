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
struct comedi_subdevice {int (* cancel ) (struct comedi_device*,struct comedi_subdevice*) ;} ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int SRF_RUNNING ; 
 int comedi_get_subdevice_runflags (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  do_become_nonbusy (struct comedi_device*,struct comedi_subdevice*) ; 
 int stub1 (struct comedi_device*,struct comedi_subdevice*) ; 

__attribute__((used)) static int do_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	int ret = 0;

	if ((comedi_get_subdevice_runflags(s) & SRF_RUNNING) && s->cancel)
		ret = s->cancel(dev, s);

	do_become_nonbusy(dev, s);

	return ret;
}