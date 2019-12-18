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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LGUEST_SHUTDOWN_POWEROFF ; 
 int /*<<< orphan*/  LHCALL_SHUTDOWN ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  __pa (void*) ; 
 int /*<<< orphan*/  kvm_hypercall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lguest_panic(struct notifier_block *nb, unsigned long l, void *p)
{
	kvm_hypercall2(LHCALL_SHUTDOWN, __pa(p), LGUEST_SHUTDOWN_POWEROFF);
	/* The hcall won't return, but to keep gcc happy, we're "done". */
	return NOTIFY_DONE;
}