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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ strncmp (char*,char*,int) ; 

int
nbsd_pc_in_sigtramp (CORE_ADDR pc, char *func_name)
{
  /* Check for libc-provided signal trampoline.  All such trampolines
     have function names which begin with "__sigtramp".  */

  return (func_name != NULL
	  && strncmp (func_name, "__sigtramp", 10) == 0);
}