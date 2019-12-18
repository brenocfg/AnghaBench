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
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
arm_netbsd_aout_in_solib_call_trampoline (CORE_ADDR pc, char *name)
{
  if (strcmp (name, "_PROCEDURE_LINKAGE_TABLE_") == 0)
    return 1;

  return 0;
}