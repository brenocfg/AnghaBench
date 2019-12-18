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
struct tape_device {scalar_t__ medium_state; int /*<<< orphan*/  state_change_wq; } ;

/* Variables and functions */
 scalar_t__ MS_LOADED ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int
tape_std_mtload(struct tape_device *device, int count)
{
	return wait_event_interruptible(device->state_change_wq,
		(device->medium_state == MS_LOADED));
}