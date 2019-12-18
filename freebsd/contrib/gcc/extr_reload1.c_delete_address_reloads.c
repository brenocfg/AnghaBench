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
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  INTVAL (scalar_t__) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ PLUS ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  delete_address_reloads_1 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  delete_related_insns (scalar_t__) ; 
 int /*<<< orphan*/  rtx_equal_p (scalar_t__,scalar_t__) ; 
 scalar_t__ single_set (scalar_t__) ; 

__attribute__((used)) static void
delete_address_reloads (rtx dead_insn, rtx current_insn)
{
  rtx set = single_set (dead_insn);
  rtx set2, dst, prev, next;
  if (set)
    {
      rtx dst = SET_DEST (set);
      if (MEM_P (dst))
	delete_address_reloads_1 (dead_insn, XEXP (dst, 0), current_insn);
    }
  /* If we deleted the store from a reloaded post_{in,de}c expression,
     we can delete the matching adds.  */
  prev = PREV_INSN (dead_insn);
  next = NEXT_INSN (dead_insn);
  if (! prev || ! next)
    return;
  set = single_set (next);
  set2 = single_set (prev);
  if (! set || ! set2
      || GET_CODE (SET_SRC (set)) != PLUS || GET_CODE (SET_SRC (set2)) != PLUS
      || GET_CODE (XEXP (SET_SRC (set), 1)) != CONST_INT
      || GET_CODE (XEXP (SET_SRC (set2), 1)) != CONST_INT)
    return;
  dst = SET_DEST (set);
  if (! rtx_equal_p (dst, SET_DEST (set2))
      || ! rtx_equal_p (dst, XEXP (SET_SRC (set), 0))
      || ! rtx_equal_p (dst, XEXP (SET_SRC (set2), 0))
      || (INTVAL (XEXP (SET_SRC (set), 1))
	  != -INTVAL (XEXP (SET_SRC (set2), 1))))
    return;
  delete_related_insns (prev);
  delete_related_insns (next);
}