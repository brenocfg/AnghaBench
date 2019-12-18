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
struct file {struct dmxdev_filter* private_data; } ;
struct TYPE_2__ {scalar_t__ error; int /*<<< orphan*/  queue; } ;
struct dmxdev_filter {scalar_t__ state; TYPE_1__ buffer; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 scalar_t__ DMXDEV_STATE_DONE ; 
 scalar_t__ DMXDEV_STATE_GO ; 
 scalar_t__ DMXDEV_STATE_TIMEDOUT ; 
 unsigned int EINVAL ; 
 unsigned int POLLERR ; 
 unsigned int POLLIN ; 
 unsigned int POLLPRI ; 
 unsigned int POLLRDNORM ; 
 int /*<<< orphan*/  dvb_ringbuffer_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int dvb_demux_poll(struct file *file, poll_table *wait)
{
	struct dmxdev_filter *dmxdevfilter = file->private_data;
	unsigned int mask = 0;

	if (!dmxdevfilter)
		return -EINVAL;

	poll_wait(file, &dmxdevfilter->buffer.queue, wait);

	if (dmxdevfilter->state != DMXDEV_STATE_GO &&
	    dmxdevfilter->state != DMXDEV_STATE_DONE &&
	    dmxdevfilter->state != DMXDEV_STATE_TIMEDOUT)
		return 0;

	if (dmxdevfilter->buffer.error)
		mask |= (POLLIN | POLLRDNORM | POLLPRI | POLLERR);

	if (!dvb_ringbuffer_empty(&dmxdevfilter->buffer))
		mask |= (POLLIN | POLLRDNORM | POLLPRI);

	return mask;
}