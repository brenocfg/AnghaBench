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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ semaphore_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 scalar_t__ SEMAPHORE_NULL ; 
 int /*<<< orphan*/  SEMAPHORE_OPTION_NONE ; 
 int /*<<< orphan*/  semaphore_wait_internal (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (int /*<<< orphan*/ )) ; 

kern_return_t
semaphore_wait_deadline(
	semaphore_t		semaphore,
	uint64_t		deadline)
{	

	if (semaphore == SEMAPHORE_NULL)
		return KERN_INVALID_ARGUMENT;

	return(semaphore_wait_internal(semaphore,
					   SEMAPHORE_NULL,
					   deadline, SEMAPHORE_OPTION_NONE,
				       (void (*)(kern_return_t))0));
}