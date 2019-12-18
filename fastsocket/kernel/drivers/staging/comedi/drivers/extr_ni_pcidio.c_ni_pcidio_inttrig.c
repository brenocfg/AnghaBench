#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {TYPE_2__* async; } ;
struct comedi_device {int dummy; } ;
struct TYPE_6__ {TYPE_1__* mite; int /*<<< orphan*/  OpModeBits; } ;
struct TYPE_5__ {int /*<<< orphan*/ * inttrig; } ;
struct TYPE_4__ {scalar_t__ daq_io_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ OpMode ; 
 TYPE_3__* devpriv ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ni_pcidio_inttrig(struct comedi_device *dev,
			     struct comedi_subdevice *s, unsigned int trignum)
{
	if (trignum != 0)
		return -EINVAL;

	writeb(devpriv->OpModeBits, devpriv->mite->daq_io_addr + OpMode);
	s->async->inttrig = NULL;

	return 1;
}