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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ MIPS_FBSD_SIGTRAMP_STACK_MOD_END ; 
 scalar_t__ MIPS_FBSD_SIGTRAMP_STACK_MOD_START ; 

__attribute__((used)) static int
is_sigtramp_sp_modified (CORE_ADDR pc)
{
  return (pc >= MIPS_FBSD_SIGTRAMP_STACK_MOD_START &&
          pc <= MIPS_FBSD_SIGTRAMP_STACK_MOD_END);
}