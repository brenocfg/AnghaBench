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
struct TYPE_5__ {scalar_t__ cmd; scalar_t__ cmdsize; int /*<<< orphan*/  segname; } ;
typedef  TYPE_1__ kernel_segment_command_t ;
struct TYPE_6__ {unsigned long ncmds; } ;
typedef  TYPE_2__ kernel_mach_header_t ;

/* Variables and functions */
 scalar_t__ LC_SEGMENT_KERNEL ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,int) ; 

kernel_segment_command_t *
getsegbynamefromheader(
	kernel_mach_header_t	*header,
	const char		*seg_name)
{
	kernel_segment_command_t *sgp;
	unsigned long i;

	sgp = (kernel_segment_command_t *)
		((uintptr_t)header + sizeof(kernel_mach_header_t));
	for (i = 0; i < header->ncmds; i++){
		if (   sgp->cmd == LC_SEGMENT_KERNEL
		    && !strncmp(sgp->segname, seg_name, sizeof(sgp->segname)))
			return sgp;
		sgp = (kernel_segment_command_t *)((uintptr_t)sgp + sgp->cmdsize);
	}
	return (kernel_segment_command_t *)NULL;
}