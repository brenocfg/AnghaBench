#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct expr {scalar_t__ reaching_reg; size_t bitmap_index; } ;
typedef  scalar_t__ rtx ;
typedef  TYPE_1__* basic_block ;
struct TYPE_9__ {int flags; } ;
struct TYPE_8__ {size_t index; } ;

/* Variables and functions */
 scalar_t__ ADDR_DIFF_VEC ; 
 scalar_t__ ADDR_VEC ; 
 scalar_t__ BB_END (TYPE_1__*) ; 
 int /*<<< orphan*/  BB_HEAD (TYPE_1__*) ; 
 scalar_t__ CALL_P (scalar_t__) ; 
 int EDGE_ABNORMAL ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 int INSN_UID (scalar_t__) ; 
 scalar_t__ JUMP_P (scalar_t__) ; 
 scalar_t__ LABEL_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NONJUMP_INSN_P (scalar_t__) ; 
 scalar_t__ NOTE_INSN_BASIC_BLOCK_P (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 int REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REG_CC_SETTER ; 
 scalar_t__ TEST_BIT (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_label_notes (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * antloc ; 
 scalar_t__ dump_file ; 
 scalar_t__ emit_insn_after_noloc (scalar_t__,scalar_t__) ; 
 scalar_t__ emit_insn_before_noloc (scalar_t__,scalar_t__) ; 
 scalar_t__ find_first_parameter_load (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ find_reg_note (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,size_t,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcse_create_count ; 
 int /*<<< orphan*/  note_stores (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ prev_nonnote_insn (scalar_t__) ; 
 scalar_t__ prev_real_insn (scalar_t__) ; 
 scalar_t__ process_insert_insn (struct expr*) ; 
 int /*<<< orphan*/  record_set_info ; 
 scalar_t__ sets_cc0_p (int /*<<< orphan*/ ) ; 
 TYPE_3__* single_succ_edge (TYPE_1__*) ; 
 int /*<<< orphan*/  single_succ_p (TYPE_1__*) ; 
 int /*<<< orphan*/ * transp ; 

__attribute__((used)) static void
insert_insn_end_bb (struct expr *expr, basic_block bb, int pre)
{
  rtx insn = BB_END (bb);
  rtx new_insn;
  rtx reg = expr->reaching_reg;
  int regno = REGNO (reg);
  rtx pat, pat_end;

  pat = process_insert_insn (expr);
  gcc_assert (pat && INSN_P (pat));

  pat_end = pat;
  while (NEXT_INSN (pat_end) != NULL_RTX)
    pat_end = NEXT_INSN (pat_end);

  /* If the last insn is a jump, insert EXPR in front [taking care to
     handle cc0, etc. properly].  Similarly we need to care trapping
     instructions in presence of non-call exceptions.  */

  if (JUMP_P (insn)
      || (NONJUMP_INSN_P (insn)
	  && (!single_succ_p (bb)
	      || single_succ_edge (bb)->flags & EDGE_ABNORMAL)))
    {
#ifdef HAVE_cc0
      rtx note;
#endif
      /* It should always be the case that we can put these instructions
	 anywhere in the basic block with performing PRE optimizations.
	 Check this.  */
      gcc_assert (!NONJUMP_INSN_P (insn) || !pre
		  || TEST_BIT (antloc[bb->index], expr->bitmap_index)
		  || TEST_BIT (transp[bb->index], expr->bitmap_index));

      /* If this is a jump table, then we can't insert stuff here.  Since
	 we know the previous real insn must be the tablejump, we insert
	 the new instruction just before the tablejump.  */
      if (GET_CODE (PATTERN (insn)) == ADDR_VEC
	  || GET_CODE (PATTERN (insn)) == ADDR_DIFF_VEC)
	insn = prev_real_insn (insn);

#ifdef HAVE_cc0
      /* FIXME: 'twould be nice to call prev_cc0_setter here but it aborts
	 if cc0 isn't set.  */
      note = find_reg_note (insn, REG_CC_SETTER, NULL_RTX);
      if (note)
	insn = XEXP (note, 0);
      else
	{
	  rtx maybe_cc0_setter = prev_nonnote_insn (insn);
	  if (maybe_cc0_setter
	      && INSN_P (maybe_cc0_setter)
	      && sets_cc0_p (PATTERN (maybe_cc0_setter)))
	    insn = maybe_cc0_setter;
	}
#endif
      /* FIXME: What if something in cc0/jump uses value set in new insn?  */
      new_insn = emit_insn_before_noloc (pat, insn);
    }

  /* Likewise if the last insn is a call, as will happen in the presence
     of exception handling.  */
  else if (CALL_P (insn)
	   && (!single_succ_p (bb)
	       || single_succ_edge (bb)->flags & EDGE_ABNORMAL))
    {
      /* Keeping in mind SMALL_REGISTER_CLASSES and parameters in registers,
	 we search backward and place the instructions before the first
	 parameter is loaded.  Do this for everyone for consistency and a
	 presumption that we'll get better code elsewhere as well.

	 It should always be the case that we can put these instructions
	 anywhere in the basic block with performing PRE optimizations.
	 Check this.  */

      gcc_assert (!pre
		  || TEST_BIT (antloc[bb->index], expr->bitmap_index)
		  || TEST_BIT (transp[bb->index], expr->bitmap_index));

      /* Since different machines initialize their parameter registers
	 in different orders, assume nothing.  Collect the set of all
	 parameter registers.  */
      insn = find_first_parameter_load (insn, BB_HEAD (bb));

      /* If we found all the parameter loads, then we want to insert
	 before the first parameter load.

	 If we did not find all the parameter loads, then we might have
	 stopped on the head of the block, which could be a CODE_LABEL.
	 If we inserted before the CODE_LABEL, then we would be putting
	 the insn in the wrong basic block.  In that case, put the insn
	 after the CODE_LABEL.  Also, respect NOTE_INSN_BASIC_BLOCK.  */
      while (LABEL_P (insn)
	     || NOTE_INSN_BASIC_BLOCK_P (insn))
	insn = NEXT_INSN (insn);

      new_insn = emit_insn_before_noloc (pat, insn);
    }
  else
    new_insn = emit_insn_after_noloc (pat, insn);

  while (1)
    {
      if (INSN_P (pat))
	{
	  add_label_notes (PATTERN (pat), new_insn);
	  note_stores (PATTERN (pat), record_set_info, pat);
	}
      if (pat == pat_end)
	break;
      pat = NEXT_INSN (pat);
    }

  gcse_create_count++;

  if (dump_file)
    {
      fprintf (dump_file, "PRE/HOIST: end of bb %d, insn %d, ",
	       bb->index, INSN_UID (new_insn));
      fprintf (dump_file, "copying expression %d to reg %d\n",
	       expr->bitmap_index, regno);
    }
}