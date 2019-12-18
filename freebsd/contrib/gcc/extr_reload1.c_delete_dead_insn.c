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
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 int /*<<< orphan*/  REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REG_DEAD ; 
 int /*<<< orphan*/  REG_P (scalar_t__) ; 
 scalar_t__ SET ; 
 scalar_t__ SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_INSN_DELETED (scalar_t__) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 scalar_t__ find_regno_note (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ prev_real_insn (scalar_t__) ; 
 scalar_t__ reg_mentioned_p (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  side_effects_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
delete_dead_insn (rtx insn)
{
  rtx prev = prev_real_insn (insn);
  rtx prev_dest;

  /* If the previous insn sets a register that dies in our insn, delete it
     too.  */
  if (prev && GET_CODE (PATTERN (prev)) == SET
      && (prev_dest = SET_DEST (PATTERN (prev)), REG_P (prev_dest))
      && reg_mentioned_p (prev_dest, PATTERN (insn))
      && find_regno_note (insn, REG_DEAD, REGNO (prev_dest))
      && ! side_effects_p (SET_SRC (PATTERN (prev))))
    delete_dead_insn (prev);

  SET_INSN_DELETED (insn);
}