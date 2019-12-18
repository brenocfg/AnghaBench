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
struct comedi_device {unsigned int n_subdevices; struct comedi_subdevice* subdevices; } ;
struct comedi_async {int dummy; } ;

/* Variables and functions */
 int comedi_buf_write_alloc (struct comedi_async*,unsigned int) ; 
 int /*<<< orphan*/  comedi_buf_write_free (struct comedi_async*,int) ; 

int comedi_mark_buffer_written(void *d, unsigned int subdevice,
			       unsigned int num_bytes)
{
	struct comedi_device *dev = (struct comedi_device *)d;
	struct comedi_subdevice *s = dev->subdevices + subdevice;
	struct comedi_async *async;
	int bytes_written;

	if (subdevice >= dev->n_subdevices)
		return -1;
	async = s->async;
	if (async == NULL)
		return -1;
	bytes_written = comedi_buf_write_alloc(async, num_bytes);
	comedi_buf_write_free(async, bytes_written);
	if (bytes_written != num_bytes)
		return -1;
	return 0;
}