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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ current_function_epilogue_delay_list ; 
 int /*<<< orphan*/  current_function_uses_const_pool ; 
 scalar_t__ get_insns () ; 
 int /*<<< orphan*/  mark_constants (scalar_t__) ; 
 scalar_t__ n_deferred_constants ; 

__attribute__((used)) static void
mark_constant_pool (void)
{
  rtx insn, link;

  if (!current_function_uses_const_pool && n_deferred_constants == 0)
    return;

  for (insn = get_insns (); insn; insn = NEXT_INSN (insn))
    mark_constants (insn);

  for (link = current_function_epilogue_delay_list;
       link;
       link = XEXP (link, 1))
    mark_constants (XEXP (link, 0));
}