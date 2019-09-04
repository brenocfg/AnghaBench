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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_3__ {scalar_t__ ip_context; scalar_t__ ip_strict_guard; scalar_t__ ip_guarded; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  kGUARD_EXC_INCORRECT_GUARD ; 
 int /*<<< orphan*/  kGUARD_EXC_UNGUARDED ; 
 int /*<<< orphan*/  mach_port_guard_exception (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
mach_port_unguard_locked(
	ipc_port_t		port,
	mach_port_name_t	name,
	uint64_t		guard)
{
	/* Port locked and active */
	if (!port->ip_guarded) {
		/* Port already unguarded; Raise exception */
		mach_port_guard_exception(name, guard, 0, kGUARD_EXC_UNGUARDED);
		return KERN_INVALID_ARGUMENT;
	}

	if (port->ip_context != guard) {
		/* Incorrect guard; Raise exception */
		mach_port_guard_exception(name, guard, port->ip_context, kGUARD_EXC_INCORRECT_GUARD);
		return KERN_INVALID_ARGUMENT;
	}

	port->ip_context = 0;
	port->ip_guarded = port->ip_strict_guard = 0;
	return KERN_SUCCESS;
}