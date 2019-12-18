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
struct comedi_subdevice {int /*<<< orphan*/  async; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int mite_buf_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_ring (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  private (struct comedi_device*) ; 
 int /*<<< orphan*/  subdev_to_counter (struct comedi_subdevice*) ; 

__attribute__((used)) static int ni_660x_buf_change(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      unsigned long new_size)
{
	int ret;

	ret = mite_buf_change(mite_ring(private(dev), subdev_to_counter(s)),
			      s->async);
	if (ret < 0)
		return ret;

	return 0;
}