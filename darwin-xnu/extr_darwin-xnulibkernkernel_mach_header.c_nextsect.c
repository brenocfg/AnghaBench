#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {uintptr_t nsects; } ;
typedef  TYPE_1__ kernel_segment_command_t ;
typedef  int /*<<< orphan*/  kernel_section_t ;

/* Variables and functions */
 int /*<<< orphan*/ * firstsect (TYPE_1__*) ; 

kernel_section_t *
nextsect(kernel_segment_command_t *sgp, kernel_section_t *sp)
{
	kernel_section_t *fsp = firstsect(sgp);

	if (((uintptr_t)(sp - fsp) + 1) >= sgp->nsects)
		return (kernel_section_t *)NULL;

	return sp+1;
}