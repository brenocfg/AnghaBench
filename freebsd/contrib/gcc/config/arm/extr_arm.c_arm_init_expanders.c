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
 int /*<<< orphan*/  PARM_BOUNDARY ; 
 int /*<<< orphan*/  arg_pointer_rtx ; 
 int /*<<< orphan*/  arm_init_machine_status ; 
 scalar_t__ cfun ; 
 int /*<<< orphan*/  init_machine_status ; 
 int /*<<< orphan*/  mark_reg_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
arm_init_expanders (void)
{
  /* Arrange to initialize and mark the machine per-function status.  */
  init_machine_status = arm_init_machine_status;

  /* This is to stop the combine pass optimizing away the alignment
     adjustment of va_arg.  */
  /* ??? It is claimed that this should not be necessary.  */
  if (cfun)
    mark_reg_pointer (arg_pointer_rtx, PARM_BOUNDARY);
}