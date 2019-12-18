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
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xb_data_to_read () ; 
 int /*<<< orphan*/  xb_waitq ; 

int xb_wait_for_data_to_read(void)
{
	return wait_event_interruptible(xb_waitq, xb_data_to_read());
}