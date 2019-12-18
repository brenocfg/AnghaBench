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
struct semaphore_signal_all_trap_args {int /*<<< orphan*/  signal_name; } ;
typedef  int /*<<< orphan*/  semaphore_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_NOT_WAITING ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  SEMAPHORE_SIGNAL_ALL ; 
 int /*<<< orphan*/  THREAD_NULL ; 
 scalar_t__ port_name_to_semaphore (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  semaphore_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ semaphore_signal_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
semaphore_signal_all_trap(
	struct semaphore_signal_all_trap_args *args)
{
	mach_port_name_t sema_name = args->signal_name;
	semaphore_t	semaphore;
	kern_return_t kr;

	kr = port_name_to_semaphore(sema_name, &semaphore);
	if (kr == KERN_SUCCESS) {
		kr = semaphore_signal_internal(semaphore,
				THREAD_NULL, 
				SEMAPHORE_SIGNAL_ALL);
		semaphore_dereference(semaphore);
		if (kr == KERN_NOT_WAITING)
			kr = KERN_SUCCESS;
	}
	return kr;
}