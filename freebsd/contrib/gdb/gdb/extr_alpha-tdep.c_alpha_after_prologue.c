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
struct symtab_and_line {scalar_t__ end; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 struct symtab_and_line find_pc_line (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_pc_partial_function (scalar_t__,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 

CORE_ADDR
alpha_after_prologue (CORE_ADDR pc)
{
  struct symtab_and_line sal;
  CORE_ADDR func_addr, func_end;

  if (!find_pc_partial_function (pc, NULL, &func_addr, &func_end))
    return 0;

  sal = find_pc_line (func_addr, 0);
  if (sal.end < func_end)
    return sal.end;

  /* The line after the prologue is after the end of the function.  In this
     case, tell the caller to find the prologue the hard way.  */
  return 0;
}