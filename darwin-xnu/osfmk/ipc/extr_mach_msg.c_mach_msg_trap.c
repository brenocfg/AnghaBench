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
struct mach_msg_overwrite_trap_args {scalar_t__ rcv_msg; } ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  int /*<<< orphan*/  mach_msg_return_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  mach_msg_overwrite_trap (struct mach_msg_overwrite_trap_args*) ; 

mach_msg_return_t
mach_msg_trap(
	struct mach_msg_overwrite_trap_args *args)
{
	kern_return_t kr;
	args->rcv_msg = (mach_vm_address_t)0;

 	kr = mach_msg_overwrite_trap(args);
	return kr;
}