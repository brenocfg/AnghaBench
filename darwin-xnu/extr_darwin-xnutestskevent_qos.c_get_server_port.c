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
 int /*<<< orphan*/  KEVENT_QOS_SERVICE_NAME ; 
 int /*<<< orphan*/  T_ASSERT_MACH_SUCCESS (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  bootstrap_check_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bootstrap_port ; 

__attribute__((used)) static mach_port_t
get_server_port(void)
{
	mach_port_t port;
	kern_return_t kr = bootstrap_check_in(bootstrap_port,
			KEVENT_QOS_SERVICE_NAME, &port);
	T_QUIET; T_ASSERT_MACH_SUCCESS(kr, "server bootstrap_check_in");
	return port;
}