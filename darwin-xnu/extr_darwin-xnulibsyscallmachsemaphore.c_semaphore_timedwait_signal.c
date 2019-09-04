#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  TYPE_1__ mach_timespec_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  semaphore_timedwait_signal_trap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
semaphore_timedwait_signal(mach_port_t wait_semaphore,
			   mach_port_t signal_semaphore,
			   mach_timespec_t wait_time)
{
        return semaphore_timedwait_signal_trap(wait_semaphore,
                                               signal_semaphore,
                                               wait_time.tv_sec,
                                               wait_time.tv_nsec);
}