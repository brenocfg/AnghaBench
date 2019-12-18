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
typedef  int /*<<< orphan*/  alpha_extra_func_info_t ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ alpha_mdebug_after_prologue (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
alpha_mdebug_in_prologue (CORE_ADDR pc, alpha_extra_func_info_t proc_desc)
{
  CORE_ADDR after_prologue_pc = alpha_mdebug_after_prologue (pc, proc_desc);
  return (after_prologue_pc == 0 || pc < after_prologue_pc);
}