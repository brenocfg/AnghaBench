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
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crw_handle_channel_report () ; 
 int /*<<< orphan*/  crw_handler_wait_q ; 
 int /*<<< orphan*/  crw_nr_req ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void crw_wait_for_channel_report(void)
{
	crw_handle_channel_report();
	wait_event(crw_handler_wait_q, atomic_read(&crw_nr_req) == 0);
}