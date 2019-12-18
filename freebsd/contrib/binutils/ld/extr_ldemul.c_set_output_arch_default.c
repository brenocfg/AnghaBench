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

/* Variables and functions */
 int /*<<< orphan*/  bfd_set_arch_mach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldfile_output_architecture ; 
 int /*<<< orphan*/  ldfile_output_machine ; 
 int /*<<< orphan*/  output_bfd ; 

void
set_output_arch_default (void)
{
  /* Set the output architecture and machine if possible.  */
  bfd_set_arch_mach (output_bfd,
		     ldfile_output_architecture, ldfile_output_machine);
}