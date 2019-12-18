#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_5__ {scalar_t__ cmd; scalar_t__ cmdsize; } ;
typedef  TYPE_1__ kernel_segment_command_t ;
struct TYPE_6__ {scalar_t__ ncmds; } ;
typedef  TYPE_2__ kernel_mach_header_t ;

/* Variables and functions */
 scalar_t__ LC_SEGMENT_KERNEL ; 

kernel_segment_command_t *
firstsegfromheader(kernel_mach_header_t *header)
{
    u_int i = 0;
    kernel_segment_command_t *sgp = (kernel_segment_command_t *)
        ((uintptr_t)header + sizeof(*header));

    for (i = 0; i < header->ncmds; i++){
        if (sgp->cmd == LC_SEGMENT_KERNEL)
            return sgp;
        sgp = (kernel_segment_command_t *)((uintptr_t)sgp + sgp->cmdsize);
    }
    return (kernel_segment_command_t *)NULL;
}