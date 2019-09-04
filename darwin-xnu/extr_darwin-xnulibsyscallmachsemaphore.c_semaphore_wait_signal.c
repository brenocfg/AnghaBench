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
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  semaphore_wait_signal_trap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
semaphore_wait_signal(mach_port_t wait_semaphore, mach_port_t signal_semaphore)
{
        return semaphore_wait_signal_trap(wait_semaphore, signal_semaphore);
}