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
typedef  int /*<<< orphan*/ * rtx ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FOR_INSN (int /*<<< orphan*/ *) ; 
 scalar_t__ CC0_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NEXT_INSN (int /*<<< orphan*/ *) ; 
 scalar_t__ NONJUMP_INSN_P (int /*<<< orphan*/ *) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SET_DEST (int /*<<< orphan*/ *) ; 
 scalar_t__ any_condjump_p (int /*<<< orphan*/ *) ; 
 int cprop_jump (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ onlyjump_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * single_set (int /*<<< orphan*/ *) ; 
 scalar_t__ try_replace_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
constprop_register (rtx insn, rtx from, rtx to, bool alter_jumps)
{
  rtx sset;

  /* Check for reg or cc0 setting instructions followed by
     conditional branch instructions first.  */
  if (alter_jumps
      && (sset = single_set (insn)) != NULL
      && NEXT_INSN (insn)
      && any_condjump_p (NEXT_INSN (insn)) && onlyjump_p (NEXT_INSN (insn)))
    {
      rtx dest = SET_DEST (sset);
      if ((REG_P (dest) || CC0_P (dest))
	  && cprop_jump (BLOCK_FOR_INSN (insn), insn, NEXT_INSN (insn), from, to))
	return 1;
    }

  /* Handle normal insns next.  */
  if (NONJUMP_INSN_P (insn)
      && try_replace_reg (from, to, insn))
    return 1;

  /* Try to propagate a CONST_INT into a conditional jump.
     We're pretty specific about what we will handle in this
     code, we can extend this as necessary over time.

     Right now the insn in question must look like
     (set (pc) (if_then_else ...))  */
  else if (alter_jumps && any_condjump_p (insn) && onlyjump_p (insn))
    return cprop_jump (BLOCK_FOR_INSN (insn), NULL, insn, from, to);
  return 0;
}