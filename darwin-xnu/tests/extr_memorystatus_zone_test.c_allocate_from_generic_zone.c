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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  mach_port_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_RIGHT_RECEIVE ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int getpid () ; 
 int /*<<< orphan*/  getppid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mach_port_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int /*<<< orphan*/  pause () ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void allocate_from_generic_zone(void)
{
	uint64_t i = 0;

	printf("[%d] Allocating mach_ports\n", getpid());
	for (i = 0; ; i++) {
		mach_port_t port;

		if ((mach_port_allocate(mach_task_self(), MACH_PORT_RIGHT_RECEIVE, &port)) != KERN_SUCCESS) {
			break;
		}
	}
	printf("[%d] Number of allocations: %lld\n", getpid(), i);

	/* Signal to the parent that we're done allocating */
	kill(getppid(), SIGUSR1);

	while (1) {
		pause();
	}
}