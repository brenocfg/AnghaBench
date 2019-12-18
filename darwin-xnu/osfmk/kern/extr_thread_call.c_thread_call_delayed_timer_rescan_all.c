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
 int /*<<< orphan*/  TCF_ABSOLUTE ; 
 int /*<<< orphan*/  TCF_CONTINUOUS ; 
 int THREAD_CALL_INDEX_MAX ; 
 int /*<<< orphan*/  thread_call_delayed_timer_rescan (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * thread_call_groups ; 

void
thread_call_delayed_timer_rescan_all(void) {
	for (int i = 0; i < THREAD_CALL_INDEX_MAX; i++) {
		thread_call_delayed_timer_rescan(&thread_call_groups[i], TCF_ABSOLUTE);
		thread_call_delayed_timer_rescan(&thread_call_groups[i], TCF_CONTINUOUS);
	}
}