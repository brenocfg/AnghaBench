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
struct comedi_subdevice {int n_chan; int /*<<< orphan*/  range_type_list; TYPE_1__** range_table_list; int /*<<< orphan*/  flaglist; int /*<<< orphan*/  maxdata_list; scalar_t__ maxdata; } ;
struct comedi_device {int n_subdevices; int minor; struct comedi_subdevice* subdevices; } ;
struct comedi_chaninfo {int subdev; scalar_t__ rangelist; scalar_t__ flaglist; scalar_t__ maxdata_list; } ;
struct TYPE_2__ {int length; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 scalar_t__ copy_from_user (struct comedi_chaninfo*,struct comedi_chaninfo*,int) ; 
 scalar_t__ copy_to_user (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_user (int,scalar_t__) ; 

__attribute__((used)) static int do_chaninfo_ioctl(struct comedi_device *dev,
			     struct comedi_chaninfo *arg)
{
	struct comedi_subdevice *s;
	struct comedi_chaninfo it;

	if (copy_from_user(&it, arg, sizeof(struct comedi_chaninfo)))
		return -EFAULT;

	if (it.subdev >= dev->n_subdevices)
		return -EINVAL;
	s = dev->subdevices + it.subdev;

	if (it.maxdata_list) {
		if (s->maxdata || !s->maxdata_list)
			return -EINVAL;
		if (copy_to_user(it.maxdata_list, s->maxdata_list,
				 s->n_chan * sizeof(unsigned int)))
			return -EFAULT;
	}

	if (it.flaglist) {
		if (!s->flaglist)
			return -EINVAL;
		if (copy_to_user(it.flaglist, s->flaglist,
				 s->n_chan * sizeof(unsigned int)))
			return -EFAULT;
	}

	if (it.rangelist) {
		int i;

		if (!s->range_table_list)
			return -EINVAL;
		for (i = 0; i < s->n_chan; i++) {
			int x;

			x = (dev->minor << 28) | (it.subdev << 24) | (i << 16) |
			    (s->range_table_list[i]->length);
			put_user(x, it.rangelist + i);
		}
#if 0
		if (copy_to_user(it.rangelist, s->range_type_list,
				 s->n_chan * sizeof(unsigned int)))
			return -EFAULT;
#endif
	}

	return 0;
}