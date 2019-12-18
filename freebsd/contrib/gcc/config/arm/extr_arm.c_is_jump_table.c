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
 scalar_t__ ADDR_DIFF_VEC ; 
 scalar_t__ ADDR_VEC ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ JUMP_INSN ; 
 scalar_t__ JUMP_LABEL (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ next_real_insn (scalar_t__) ; 

__attribute__((used)) static rtx
is_jump_table (rtx insn)
{
  rtx table;

  if (GET_CODE (insn) == JUMP_INSN
      && JUMP_LABEL (insn) != NULL
      && ((table = next_real_insn (JUMP_LABEL (insn)))
	  == next_real_insn (insn))
      && table != NULL
      && GET_CODE (table) == JUMP_INSN
      && (GET_CODE (PATTERN (table)) == ADDR_VEC
	  || GET_CODE (PATTERN (table)) == ADDR_DIFF_VEC))
    return table;

  return NULL_RTX;
}