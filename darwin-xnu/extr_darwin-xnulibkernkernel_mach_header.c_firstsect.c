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
struct TYPE_3__ {scalar_t__ nsects; } ;
typedef  TYPE_1__ kernel_segment_command_t ;
typedef  int /*<<< orphan*/  kernel_section_t ;

/* Variables and functions */

kernel_section_t *
firstsect(kernel_segment_command_t *sgp)
{
	if (!sgp || sgp->nsects == 0)
		return (kernel_section_t *)NULL;

	return (kernel_section_t *)(sgp+1);
}