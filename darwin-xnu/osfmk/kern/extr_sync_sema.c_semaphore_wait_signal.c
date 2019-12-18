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
typedef  scalar_t__ semaphore_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 scalar_t__ SEMAPHORE_NULL ; 
 int /*<<< orphan*/  SEMAPHORE_OPTION_NONE ; 
 int /*<<< orphan*/  semaphore_wait_internal (scalar_t__,scalar_t__,unsigned long long,int /*<<< orphan*/ ,void (*) (int /*<<< orphan*/ )) ; 

kern_return_t
semaphore_wait_signal(
	semaphore_t		wait_semaphore,
	semaphore_t		signal_semaphore)
{
	if (wait_semaphore == SEMAPHORE_NULL)
		return KERN_INVALID_ARGUMENT;
	
	return(semaphore_wait_internal(wait_semaphore,
				       signal_semaphore,
					   0ULL, SEMAPHORE_OPTION_NONE,
				       (void(*)(kern_return_t))0));
}