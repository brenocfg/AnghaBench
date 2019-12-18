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
struct semaphore_timedwait_trap_args {int /*<<< orphan*/  nsec; int /*<<< orphan*/  sec; int /*<<< orphan*/  wait_name; } ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  semaphore_timedwait_trap_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_syscall_return ; 

kern_return_t
semaphore_timedwait_trap(
	struct semaphore_timedwait_trap_args *args)
{	

	return(semaphore_timedwait_trap_internal(args->wait_name, args->sec, args->nsec, thread_syscall_return));
}