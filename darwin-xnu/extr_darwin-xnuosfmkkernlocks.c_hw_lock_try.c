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
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  hw_lock_t ;

/* Variables and functions */
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  disable_preemption_for_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_preemption () ; 
 unsigned int hw_lock_try_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int
hw_lock_try(hw_lock_t lock)
{
	thread_t thread = current_thread();
	disable_preemption_for_thread(thread);
	unsigned int success = hw_lock_try_internal(lock, thread);
	if (!success)
		enable_preemption();
	return success;
}