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
struct comedi_subdevice {int /*<<< orphan*/  async; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * gpct_mite_ring; } ;

/* Variables and functions */
 TYPE_1__* devpriv ; 
 int mite_buf_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcimio_gpct1_change(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       unsigned long new_size)
{
	int ret;

	ret = mite_buf_change(devpriv->gpct_mite_ring[1], s->async);
	if (ret < 0)
		return ret;

	return 0;
}