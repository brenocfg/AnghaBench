#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
typedef  scalar_t__ rtx ;
struct TYPE_2__ {int /*<<< orphan*/  decl; } ;

/* Variables and functions */
 scalar_t__ ADDR_DIFF_VEC ; 
 scalar_t__ ADDR_VEC ; 
 int /*<<< orphan*/ * DECL_INITIAL (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ JUMP_P (scalar_t__) ; 
 int /*<<< orphan*/  NOTE_INSN_DELETED ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ SEQUENCE ; 
 scalar_t__ XVECEXP (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  active_insn_p (scalar_t__) ; 
 TYPE_1__* cfun ; 
 int /*<<< orphan*/  change_scope (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * choose_inner_scope (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_insn (scalar_t__) ; 
 scalar_t__ emit_note (int /*<<< orphan*/ ) ; 
 scalar_t__ get_insns () ; 
 int /*<<< orphan*/ * insn_scope (scalar_t__) ; 
 scalar_t__ next_active_insn (scalar_t__) ; 
 int /*<<< orphan*/  reorder_blocks () ; 

void
reemit_insn_block_notes (void)
{
  tree cur_block = DECL_INITIAL (cfun->decl);
  rtx insn, note;

  insn = get_insns ();
  if (!active_insn_p (insn))
    insn = next_active_insn (insn);
  for (; insn; insn = next_active_insn (insn))
    {
      tree this_block;

      /* Avoid putting scope notes between jump table and its label.  */
      if (JUMP_P (insn)
	  && (GET_CODE (PATTERN (insn)) == ADDR_VEC
	      || GET_CODE (PATTERN (insn)) == ADDR_DIFF_VEC))
	continue;

      this_block = insn_scope (insn);
      /* For sequences compute scope resulting from merging all scopes
	 of instructions nested inside.  */
      if (GET_CODE (PATTERN (insn)) == SEQUENCE)
	{
	  int i;
	  rtx body = PATTERN (insn);

	  this_block = NULL;
	  for (i = 0; i < XVECLEN (body, 0); i++)
	    this_block = choose_inner_scope (this_block,
					 insn_scope (XVECEXP (body, 0, i)));
	}
      if (! this_block)
	continue;

      if (this_block != cur_block)
	{
	  change_scope (insn, cur_block, this_block);
	  cur_block = this_block;
	}
    }

  /* change_scope emits before the insn, not after.  */
  note = emit_note (NOTE_INSN_DELETED);
  change_scope (note, cur_block, DECL_INITIAL (cfun->decl));
  delete_insn (note);

  reorder_blocks ();
}