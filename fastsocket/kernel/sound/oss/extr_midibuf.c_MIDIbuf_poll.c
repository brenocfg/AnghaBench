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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 scalar_t__ DATA_AVAIL (int /*<<< orphan*/ ) ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 int /*<<< orphan*/  SPACE_AVAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * input_sleeper ; 
 int /*<<< orphan*/ * midi_in_buf ; 
 int /*<<< orphan*/ * midi_out_buf ; 
 int /*<<< orphan*/ * midi_sleeper ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

unsigned int MIDIbuf_poll(int dev, struct file *file, poll_table * wait)
{
	unsigned int mask = 0;

	dev = dev >> 4;

	/* input */
	poll_wait(file, &input_sleeper[dev], wait);
	if (DATA_AVAIL(midi_in_buf[dev]))
		mask |= POLLIN | POLLRDNORM;

	/* output */
	poll_wait(file, &midi_sleeper[dev], wait);
	if (!SPACE_AVAIL(midi_out_buf[dev]))
		mask |= POLLOUT | POLLWRNORM;
	
	return mask;
}