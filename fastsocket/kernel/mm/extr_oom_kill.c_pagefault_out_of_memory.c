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
 int /*<<< orphan*/  TIF_MEMDIE ; 
 int /*<<< orphan*/  clear_system_oom () ; 
 int /*<<< orphan*/  out_of_memory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 
 scalar_t__ try_set_system_oom () ; 

void pagefault_out_of_memory(void)
{
	if (try_set_system_oom()) {
		out_of_memory(NULL, 0, 0, NULL);
		clear_system_oom();
	}
	if (!test_thread_flag(TIF_MEMDIE))
		schedule_timeout_uninterruptible(1);
}