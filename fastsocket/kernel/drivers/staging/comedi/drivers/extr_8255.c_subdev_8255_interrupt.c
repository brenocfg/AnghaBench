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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK_ARG ; 
 int CALLBACK_FUNC (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMEDI_CB_EOS ; 
 scalar_t__ _8255_DATA ; 
 int /*<<< orphan*/  comedi_buf_put (TYPE_1__*,short) ; 
 int /*<<< orphan*/  comedi_event (struct comedi_device*,struct comedi_subdevice*) ; 

void subdev_8255_interrupt(struct comedi_device *dev,
			   struct comedi_subdevice *s)
{
	short d;

	d = CALLBACK_FUNC(0, _8255_DATA, 0, CALLBACK_ARG);
	d |= (CALLBACK_FUNC(0, _8255_DATA + 1, 0, CALLBACK_ARG) << 8);

	comedi_buf_put(s->async, d);
	s->async->events |= COMEDI_CB_EOS;

	comedi_event(dev, s);
}