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
struct comedi_subdevice {int n_chan; struct comedi_lrange** range_table_list; struct comedi_lrange* range_table; } ;
struct comedi_rangeinfo {int range_type; int /*<<< orphan*/  range_ptr; } ;
struct comedi_lrange {int length; int /*<<< orphan*/  range; } ;
struct comedi_krange {int dummy; } ;
struct comedi_device {int n_subdevices; struct comedi_subdevice* subdevices; int /*<<< orphan*/  attached; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int,int,int) ; 
 int EFAULT ; 
 int EINVAL ; 
 int RANGE_LENGTH (int) ; 
 scalar_t__ copy_from_user (struct comedi_rangeinfo*,struct comedi_rangeinfo*,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int do_rangeinfo_ioctl(struct comedi_device *dev, struct comedi_rangeinfo *arg)
{
	struct comedi_rangeinfo it;
	int subd, chan;
	const struct comedi_lrange *lr;
	struct comedi_subdevice *s;

	if (copy_from_user(&it, arg, sizeof(struct comedi_rangeinfo)))
		return -EFAULT;
	subd = (it.range_type >> 24) & 0xf;
	chan = (it.range_type >> 16) & 0xff;

	if (!dev->attached)
		return -EINVAL;
	if (subd >= dev->n_subdevices)
		return -EINVAL;
	s = dev->subdevices + subd;
	if (s->range_table) {
		lr = s->range_table;
	} else if (s->range_table_list) {
		if (chan >= s->n_chan)
			return -EINVAL;
		lr = s->range_table_list[chan];
	} else {
		return -EINVAL;
	}

	if (RANGE_LENGTH(it.range_type) != lr->length) {
		DPRINTK("wrong length %d should be %d (0x%08x)\n",
			RANGE_LENGTH(it.range_type), lr->length, it.range_type);
		return -EINVAL;
	}

	if (copy_to_user(it.range_ptr, lr->range,
			 sizeof(struct comedi_krange) * lr->length))
		return -EFAULT;

	return 0;
}