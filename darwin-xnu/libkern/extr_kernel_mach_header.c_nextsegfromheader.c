#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_6__ {scalar_t__ cmd; scalar_t__ cmdsize; } ;
typedef  TYPE_1__ kernel_segment_command_t ;
struct TYPE_7__ {scalar_t__ ncmds; } ;
typedef  TYPE_2__ kernel_mach_header_t ;

/* Variables and functions */
 scalar_t__ LC_SEGMENT_KERNEL ; 

kernel_segment_command_t *
nextsegfromheader(
        kernel_mach_header_t	*header,
        kernel_segment_command_t	*seg)
{
    u_int i = 0;
    kernel_segment_command_t *sgp = (kernel_segment_command_t *)
        ((uintptr_t)header + sizeof(*header));

    /* Find the index of the passed-in segment */
    for (i = 0; sgp != seg && i < header->ncmds; i++) {
        sgp = (kernel_segment_command_t *)((uintptr_t)sgp + sgp->cmdsize);
    }

    /* Increment to the next load command */
    i++;
    sgp = (kernel_segment_command_t *)((uintptr_t)sgp + sgp->cmdsize);

    /* Return the next segment command, if any */
    for (; i < header->ncmds; i++) {
        if (sgp->cmd == LC_SEGMENT_KERNEL) return sgp;

        sgp = (kernel_segment_command_t *)((uintptr_t)sgp + sgp->cmdsize);
    }

    return (kernel_segment_command_t *)NULL;
}