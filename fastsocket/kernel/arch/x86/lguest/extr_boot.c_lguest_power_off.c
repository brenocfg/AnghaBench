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

/* Variables and functions */
 int /*<<< orphan*/  LGUEST_SHUTDOWN_POWEROFF ; 
 int /*<<< orphan*/  LHCALL_SHUTDOWN ; 
 int /*<<< orphan*/  __pa (char*) ; 
 int /*<<< orphan*/  kvm_hypercall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lguest_power_off(void)
{
	kvm_hypercall2(LHCALL_SHUTDOWN, __pa("Power down"),
					LGUEST_SHUTDOWN_POWEROFF);
}