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
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpqhp_event_thread ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  event_thread ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

int cpqhp_event_start_thread(void)
{
	cpqhp_event_thread = kthread_run(event_thread, NULL, "phpd_event");
	if (IS_ERR(cpqhp_event_thread)) {
		err ("Can't start up our event thread\n");
		return PTR_ERR(cpqhp_event_thread);
	}

	return 0;
}