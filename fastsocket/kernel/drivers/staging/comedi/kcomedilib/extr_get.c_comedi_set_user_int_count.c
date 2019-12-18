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
struct comedi_device {struct comedi_subdevice* subdevices; } ;
struct comedi_async {unsigned int buf_read_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_buf_read_alloc (struct comedi_async*,int) ; 
 int /*<<< orphan*/  comedi_buf_read_free (struct comedi_async*,int) ; 

int comedi_set_user_int_count(void *d, unsigned int subdevice,
			      unsigned int buf_user_count)
{
	struct comedi_device *dev = (struct comedi_device *)d;
	struct comedi_subdevice *s = dev->subdevices + subdevice;
	struct comedi_async *async;
	int num_bytes;

	async = s->async;
	if (async == NULL)
		return -1;

	num_bytes = buf_user_count - async->buf_read_count;
	if (num_bytes < 0)
		return -1;
	comedi_buf_read_alloc(async, num_bytes);
	comedi_buf_read_free(async, num_bytes);

	return 0;
}