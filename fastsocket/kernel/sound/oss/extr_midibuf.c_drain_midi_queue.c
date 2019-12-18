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
struct TYPE_2__ {scalar_t__ (* buffer_status ) (int) ;} ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  interruptible_sleep_on_timeout (int /*<<< orphan*/ *,int) ; 
 TYPE_1__** midi_devs ; 
 int /*<<< orphan*/ * midi_sleeper ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int) ; 

__attribute__((used)) static void drain_midi_queue(int dev)
{

	/*
	 * Give the Midi driver time to drain its output queues
	 */

	if (midi_devs[dev]->buffer_status != NULL)
		while (!signal_pending(current) && midi_devs[dev]->buffer_status(dev)) 
			interruptible_sleep_on_timeout(&midi_sleeper[dev],
						       HZ/10);
}