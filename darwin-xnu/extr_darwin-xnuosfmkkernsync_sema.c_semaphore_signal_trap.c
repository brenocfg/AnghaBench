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
struct semaphore_signal_trap_args {int /*<<< orphan*/  signal_name; } ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  semaphore_signal_internal_trap (int /*<<< orphan*/ ) ; 

kern_return_t
semaphore_signal_trap(
	struct semaphore_signal_trap_args *args)
{
	mach_port_name_t sema_name = args->signal_name;

	return (semaphore_signal_internal_trap(sema_name));
}