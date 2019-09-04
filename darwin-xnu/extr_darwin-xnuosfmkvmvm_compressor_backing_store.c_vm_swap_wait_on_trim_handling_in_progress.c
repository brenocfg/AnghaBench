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
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ delayed_trim_handling_in_progress ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_swap_data_lock ; 

__attribute__((used)) static void
vm_swap_wait_on_trim_handling_in_progress()
{
	while (delayed_trim_handling_in_progress == TRUE) {

		assert_wait((event_t) &delayed_trim_handling_in_progress, THREAD_UNINT);
		lck_mtx_unlock(&vm_swap_data_lock);
		
		thread_block(THREAD_CONTINUE_NULL);
		
		lck_mtx_lock(&vm_swap_data_lock);
	}
}