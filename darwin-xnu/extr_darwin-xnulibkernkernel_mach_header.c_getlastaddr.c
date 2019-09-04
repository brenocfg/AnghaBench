#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct TYPE_4__ {scalar_t__ cmd; scalar_t__ vmaddr; scalar_t__ vmsize; scalar_t__ cmdsize; } ;
typedef  TYPE_1__ kernel_segment_command_t ;
struct TYPE_5__ {unsigned long ncmds; } ;
typedef  TYPE_2__ kernel_mach_header_t ;

/* Variables and functions */
 scalar_t__ LC_SEGMENT_KERNEL ; 
 TYPE_2__ _mh_execute_header ; 

vm_offset_t
getlastaddr(void)
{
	kernel_segment_command_t	*sgp;
	vm_offset_t		last_addr = 0;
	kernel_mach_header_t *header = &_mh_execute_header;
	unsigned long i;

	sgp = (kernel_segment_command_t *)
		((uintptr_t)header + sizeof(kernel_mach_header_t));
	for (i = 0; i < header->ncmds; i++){
		if (sgp->cmd == LC_SEGMENT_KERNEL) {
			if (sgp->vmaddr + sgp->vmsize > last_addr)
				last_addr = sgp->vmaddr + sgp->vmsize;
		}
		sgp = (kernel_segment_command_t *)((uintptr_t)sgp + sgp->cmdsize);
	}
	return last_addr;
}