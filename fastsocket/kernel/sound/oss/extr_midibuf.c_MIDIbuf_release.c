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
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* close ) (int) ;int /*<<< orphan*/  (* outputc ) (int,int) ;} ;

/* Variables and functions */
 scalar_t__ DATA_AVAIL (int /*<<< orphan*/ *) ; 
 int OPEN_READ ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drain_midi_queue (int) ; 
 int /*<<< orphan*/  interruptible_sleep_on (int /*<<< orphan*/ *) ; 
 TYPE_1__** midi_devs ; 
 int /*<<< orphan*/ ** midi_in_buf ; 
 int /*<<< orphan*/ ** midi_out_buf ; 
 int /*<<< orphan*/ * midi_sleeper ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int num_midis ; 
 scalar_t__ open_devs ; 
 int /*<<< orphan*/  poll_timer ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int translate_mode (struct file*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void MIDIbuf_release(int dev, struct file *file)
{
	int mode;

	dev = dev >> 4;
	mode = translate_mode(file);

	if (dev < 0 || dev >= num_midis || midi_devs[dev] == NULL)
		return;

	/*
	 * Wait until the queue is empty
	 */

	if (mode != OPEN_READ)
	{
		midi_devs[dev]->outputc(dev, 0xfe);	/*
							   * Active sensing to shut the
							   * devices
							 */

		while (!signal_pending(current) && DATA_AVAIL(midi_out_buf[dev]))
			  interruptible_sleep_on(&midi_sleeper[dev]);
		/*
		 *	Sync
		 */

		drain_midi_queue(dev);	/*
					 * Ensure the output queues are empty
					 */
	}

	midi_devs[dev]->close(dev);

	open_devs--;
	if (open_devs == 0)
		del_timer_sync(&poll_timer);
	vfree(midi_in_buf[dev]);
	vfree(midi_out_buf[dev]);
	midi_in_buf[dev] = NULL;
	midi_out_buf[dev] = NULL;

	module_put(midi_devs[dev]->owner);
}