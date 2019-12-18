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
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  test_once_thread_call () ; 
 int /*<<< orphan*/  test_signal_thread_call () ; 

kern_return_t
test_thread_call(void)
{
	test_once_thread_call();
	test_signal_thread_call();

	return KERN_SUCCESS;
}