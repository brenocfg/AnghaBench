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
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {scalar_t__ n_subdevices; struct comedi_subdevice* subdevices; } ;
struct comedi_bufconfig {scalar_t__ subdevice; scalar_t__ maximum_size; scalar_t__ size; } ;
struct comedi_async {scalar_t__ max_bufsize; scalar_t__ prealloc_bufsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int EFAULT ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ copy_from_user (struct comedi_bufconfig*,void*,int) ; 
 scalar_t__ copy_to_user (void*,struct comedi_bufconfig*,int) ; 
 int resize_async_buffer (struct comedi_device*,struct comedi_subdevice*,struct comedi_async*,scalar_t__) ; 

__attribute__((used)) static int do_bufconfig_ioctl(struct comedi_device *dev, void *arg)
{
	struct comedi_bufconfig bc;
	struct comedi_async *async;
	struct comedi_subdevice *s;
	int retval = 0;

	if (copy_from_user(&bc, arg, sizeof(struct comedi_bufconfig)))
		return -EFAULT;

	if (bc.subdevice >= dev->n_subdevices || bc.subdevice < 0)
		return -EINVAL;

	s = dev->subdevices + bc.subdevice;
	async = s->async;

	if (!async) {
		DPRINTK("subdevice does not have async capability\n");
		bc.size = 0;
		bc.maximum_size = 0;
		goto copyback;
	}

	if (bc.maximum_size) {
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;

		async->max_bufsize = bc.maximum_size;
	}

	if (bc.size) {
		retval = resize_async_buffer(dev, s, async, bc.size);
		if (retval < 0)
			return retval;
	}

	bc.size = async->prealloc_bufsz;
	bc.maximum_size = async->max_bufsize;

copyback:
	if (copy_to_user(arg, &bc, sizeof(struct comedi_bufconfig)))
		return -EFAULT;

	return 0;
}