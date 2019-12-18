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
struct comedi_subdevice {int subdev_flags; struct comedi_async* async; } ;
struct comedi_device {scalar_t__ n_subdevices; struct comedi_subdevice* subdevices; } ;
struct comedi_bufinfo {scalar_t__ subdevice; scalar_t__ buf_write_count; scalar_t__ buf_read_count; scalar_t__ buf_read_ptr; scalar_t__ buf_write_ptr; scalar_t__ bytes_written; scalar_t__ bytes_read; } ;
struct comedi_async {scalar_t__ buf_write_count; scalar_t__ buf_read_count; scalar_t__ buf_read_ptr; scalar_t__ buf_write_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int EFAULT ; 
 int EINVAL ; 
 int SDF_CMD_READ ; 
 int SDF_CMD_WRITE ; 
 int SRF_ERROR ; 
 int SRF_RUNNING ; 
 scalar_t__ comedi_buf_read_alloc (struct comedi_async*,scalar_t__) ; 
 int /*<<< orphan*/  comedi_buf_read_free (struct comedi_async*,scalar_t__) ; 
 scalar_t__ comedi_buf_write_alloc (struct comedi_async*,scalar_t__) ; 
 int /*<<< orphan*/  comedi_buf_write_free (struct comedi_async*,scalar_t__) ; 
 int comedi_get_subdevice_runflags (struct comedi_subdevice*) ; 
 scalar_t__ copy_from_user (struct comedi_bufinfo*,void*,int) ; 
 scalar_t__ copy_to_user (void*,struct comedi_bufinfo*,int) ; 
 int /*<<< orphan*/  do_become_nonbusy (struct comedi_device*,struct comedi_subdevice*) ; 

__attribute__((used)) static int do_bufinfo_ioctl(struct comedi_device *dev, void *arg)
{
	struct comedi_bufinfo bi;
	struct comedi_subdevice *s;
	struct comedi_async *async;

	if (copy_from_user(&bi, arg, sizeof(struct comedi_bufinfo)))
		return -EFAULT;

	if (bi.subdevice >= dev->n_subdevices || bi.subdevice < 0)
		return -EINVAL;

	s = dev->subdevices + bi.subdevice;
	async = s->async;

	if (!async) {
		DPRINTK("subdevice does not have async capability\n");
		bi.buf_write_ptr = 0;
		bi.buf_read_ptr = 0;
		bi.buf_write_count = 0;
		bi.buf_read_count = 0;
		goto copyback;
	}

	if (bi.bytes_read && (s->subdev_flags & SDF_CMD_READ)) {
		bi.bytes_read = comedi_buf_read_alloc(async, bi.bytes_read);
		comedi_buf_read_free(async, bi.bytes_read);

		if (!(comedi_get_subdevice_runflags(s) & (SRF_ERROR |
							  SRF_RUNNING))
		    && async->buf_write_count == async->buf_read_count) {
			do_become_nonbusy(dev, s);
		}
	}

	if (bi.bytes_written && (s->subdev_flags & SDF_CMD_WRITE)) {
		bi.bytes_written =
		    comedi_buf_write_alloc(async, bi.bytes_written);
		comedi_buf_write_free(async, bi.bytes_written);
	}

	bi.buf_write_count = async->buf_write_count;
	bi.buf_write_ptr = async->buf_write_ptr;
	bi.buf_read_count = async->buf_read_count;
	bi.buf_read_ptr = async->buf_read_ptr;

copyback:
	if (copy_to_user(arg, &bi, sizeof(struct comedi_bufinfo)))
		return -EFAULT;

	return 0;
}