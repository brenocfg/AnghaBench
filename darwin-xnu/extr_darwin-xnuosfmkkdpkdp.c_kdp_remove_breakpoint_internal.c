#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_vm_size_t ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  int /*<<< orphan*/  kdp_error_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  bytesused; int /*<<< orphan*/  oldbytes; scalar_t__ address; } ;

/* Variables and functions */
 int /*<<< orphan*/  KDPERR_BREAKPOINT_NOT_FOUND ; 
 int /*<<< orphan*/  KDPERR_NO_ERROR ; 
 int MAX_BREAKPOINTS ; 
 TYPE_1__* breakpoint_list ; 
 int /*<<< orphan*/  kdp_machine_vm_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

kdp_error_t
kdp_remove_breakpoint_internal(
    mach_vm_address_t	address
)
{
	mach_vm_size_t	cnt;
	int		i;
	
	for(i=0;(i < MAX_BREAKPOINTS) && (breakpoint_list[i].address != address); i++);
	
	if (i == MAX_BREAKPOINTS)
	{
		return KDPERR_BREAKPOINT_NOT_FOUND; 
	}
	
	breakpoint_list[i].address = 0;
	cnt = kdp_machine_vm_write((caddr_t)&breakpoint_list[i].oldbytes, address, breakpoint_list[i].bytesused);
	
	return KDPERR_NO_ERROR;
}