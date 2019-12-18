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
struct no_conflict_data {int must_stay; scalar_t__ insn; scalar_t__ first; int /*<<< orphan*/  target; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ CALL_P (scalar_t__) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USE ; 
 scalar_t__ find_reg_fusage (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ modified_between_p (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ modified_in_p (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ reg_overlap_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ reg_used_between_p (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
no_conflict_move_test (rtx dest, rtx set, void *p0)
{
  struct no_conflict_data *p= p0;

  /* If this inns directly contributes to setting the target, it must stay.  */
  if (reg_overlap_mentioned_p (p->target, dest))
    p->must_stay = true;
  /* If we haven't committed to keeping any other insns in the list yet,
     there is nothing more to check.  */
  else if (p->insn == p->first)
    return;
  /* If this insn sets / clobbers a register that feeds one of the insns
     already in the list, this insn has to stay too.  */
  else if (reg_overlap_mentioned_p (dest, PATTERN (p->first))
	   || (CALL_P (p->first) && (find_reg_fusage (p->first, USE, dest)))
	   || reg_used_between_p (dest, p->first, p->insn)
	   /* Likewise if this insn depends on a register set by a previous
	      insn in the list, or if it sets a result (presumably a hard
	      register) that is set or clobbered by a previous insn.
	      N.B. the modified_*_p (SET_DEST...) tests applied to a MEM
	      SET_DEST perform the former check on the address, and the latter
	      check on the MEM.  */
	   || (GET_CODE (set) == SET
	       && (modified_in_p (SET_SRC (set), p->first)
		   || modified_in_p (SET_DEST (set), p->first)
		   || modified_between_p (SET_SRC (set), p->first, p->insn)
		   || modified_between_p (SET_DEST (set), p->first, p->insn))))
    p->must_stay = true;
}