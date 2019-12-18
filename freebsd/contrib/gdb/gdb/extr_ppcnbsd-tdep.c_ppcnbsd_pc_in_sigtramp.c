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
 int nbsd_pc_in_sigtramp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ppcnbsd_pc_in_sigtramp (CORE_ADDR pc, char *func_name)
{
  /* FIXME: Need to add support for kernel-provided signal trampolines.  */
  return (nbsd_pc_in_sigtramp (pc, func_name));
}