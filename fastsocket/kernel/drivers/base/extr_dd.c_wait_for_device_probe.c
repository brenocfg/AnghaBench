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

/* Variables and functions */
 int /*<<< orphan*/  async_synchronize_full () ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  probe_count ; 
 int /*<<< orphan*/  probe_waitqueue ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void wait_for_device_probe(void)
{
	/* wait for the known devices to complete their probing */
	wait_event(probe_waitqueue, atomic_read(&probe_count) == 0);
	async_synchronize_full();
}