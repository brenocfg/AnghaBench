#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ semaphore_t ;
struct TYPE_4__ {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
typedef  TYPE_1__ mach_timespec_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 scalar_t__ BAD_MACH_TIMESPEC (TYPE_1__*) ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_INVALID_VALUE ; 
 scalar_t__ SEMAPHORE_NULL ; 
 int SEMAPHORE_OPTION_NONE ; 
 int SEMAPHORE_TIMEOUT_NOBLOCK ; 
 int /*<<< orphan*/  semaphore_deadline (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  semaphore_wait_internal (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,void (*) (int /*<<< orphan*/ )) ; 

kern_return_t
semaphore_timedwait_signal(
	semaphore_t		wait_semaphore,
	semaphore_t		signal_semaphore,
	mach_timespec_t		wait_time)
{
	int				option = SEMAPHORE_OPTION_NONE;
	uint64_t		deadline = 0;

	if (wait_semaphore == SEMAPHORE_NULL)
		return KERN_INVALID_ARGUMENT;
	
	if(BAD_MACH_TIMESPEC(&wait_time))
		return KERN_INVALID_VALUE;

	if (wait_time.tv_sec == 0 && wait_time.tv_nsec == 0)
		option = SEMAPHORE_TIMEOUT_NOBLOCK;
	else
		deadline = semaphore_deadline(wait_time.tv_sec, wait_time.tv_nsec);
	
	return(semaphore_wait_internal(wait_semaphore,
				       signal_semaphore,
					   deadline, option,
				       (void(*)(kern_return_t))0));
}