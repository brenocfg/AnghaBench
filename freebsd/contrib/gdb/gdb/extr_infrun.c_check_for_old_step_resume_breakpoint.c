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
 scalar_t__ step_resume_breakpoint ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static void
check_for_old_step_resume_breakpoint (void)
{
  if (step_resume_breakpoint)
    warning
      ("GDB bug: infrun.c (wait_for_inferior): dropping old step_resume breakpoint");
}