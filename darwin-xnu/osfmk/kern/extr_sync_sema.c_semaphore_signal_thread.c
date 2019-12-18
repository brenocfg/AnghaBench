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
typedef  scalar_t__ semaphore_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 scalar_t__ SEMAPHORE_NULL ; 
 int /*<<< orphan*/  SEMAPHORE_OPTION_NONE ; 
 int /*<<< orphan*/  semaphore_signal_internal (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
semaphore_signal_thread(
	semaphore_t	semaphore,
	thread_t	thread)
{
	kern_return_t		ret;

	if (semaphore == SEMAPHORE_NULL)
		return KERN_INVALID_ARGUMENT;

	ret = semaphore_signal_internal(semaphore,
					thread,
					SEMAPHORE_OPTION_NONE);
	return ret;
}