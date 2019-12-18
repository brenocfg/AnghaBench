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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {int ao_fifo_depth; } ;
struct TYPE_3__ {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_BLOCK ; 
 int /*<<< orphan*/  COMEDI_CB_OVERFLOW ; 
 TYPE_2__ boardtype ; 
 int comedi_buf_read_n_available (TYPE_1__*) ; 
 int /*<<< orphan*/  ni_ao_fifo_load (struct comedi_device*,struct comedi_subdevice*,int) ; 

__attribute__((used)) static int ni_ao_fifo_half_empty(struct comedi_device *dev,
				 struct comedi_subdevice *s)
{
	int n;

	n = comedi_buf_read_n_available(s->async);
	if (n == 0) {
		s->async->events |= COMEDI_CB_OVERFLOW;
		return 0;
	}

	n /= sizeof(short);
	if (n > boardtype.ao_fifo_depth / 2)
		n = boardtype.ao_fifo_depth / 2;

	ni_ao_fifo_load(dev, s, n);

	s->async->events |= COMEDI_CB_BLOCK;

	return 1;
}