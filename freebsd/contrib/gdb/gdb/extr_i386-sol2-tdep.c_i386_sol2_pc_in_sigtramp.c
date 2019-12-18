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
typedef  int CORE_ADDR ;

/* Variables and functions */

__attribute__((used)) static int
i386_sol2_pc_in_sigtramp (CORE_ADDR pc, char *name)
{
  /* Signal handler frames under Solaris 2 are recognized by a return
     address of 0xffffffff.  */
  return (pc == 0xffffffff);
}