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
struct hash_table {scalar_t__ set_p; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ BB_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BLOCK_FOR_INSN (scalar_t__) ; 
 scalar_t__ CALL ; 
 unsigned int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  JUMP_P (scalar_t__) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 unsigned int REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REG_EH_REGION ; 
 int /*<<< orphan*/  REG_EQUIV ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ can_copy_p (int /*<<< orphan*/ ) ; 
 scalar_t__ find_reg_equal_equiv_note (scalar_t__) ; 
 scalar_t__ find_reg_note (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ flag_gcse_las ; 
 scalar_t__ gcse_constant_p (scalar_t__) ; 
 scalar_t__ gen_rtx_SET (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hash_scan_call (scalar_t__,scalar_t__,struct hash_table*) ; 
 int /*<<< orphan*/  insert_expr_in_table (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int,int,struct hash_table*) ; 
 int /*<<< orphan*/  insert_set_in_table (scalar_t__,scalar_t__,struct hash_table*) ; 
 scalar_t__ next_nonnote_insn (scalar_t__) ; 
 scalar_t__ oprs_anticipatable_p (scalar_t__,scalar_t__) ; 
 scalar_t__ oprs_available_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_noop_p (scalar_t__) ; 
 scalar_t__ single_set (scalar_t__) ; 
 scalar_t__ want_to_gcse_p (scalar_t__) ; 

__attribute__((used)) static void
hash_scan_set (rtx pat, rtx insn, struct hash_table *table)
{
  rtx src = SET_SRC (pat);
  rtx dest = SET_DEST (pat);
  rtx note;

  if (GET_CODE (src) == CALL)
    hash_scan_call (src, insn, table);

  else if (REG_P (dest))
    {
      unsigned int regno = REGNO (dest);
      rtx tmp;

      /* See if a REG_NOTE shows this equivalent to a simpler expression.
	 This allows us to do a single GCSE pass and still eliminate
	 redundant constants, addresses or other expressions that are
	 constructed with multiple instructions.  */
      note = find_reg_equal_equiv_note (insn);
      if (note != 0
	  && (table->set_p
	      ? gcse_constant_p (XEXP (note, 0))
	      : want_to_gcse_p (XEXP (note, 0))))
	src = XEXP (note, 0), pat = gen_rtx_SET (VOIDmode, dest, src);

      /* Only record sets of pseudo-regs in the hash table.  */
      if (! table->set_p
	  && regno >= FIRST_PSEUDO_REGISTER
	  /* Don't GCSE something if we can't do a reg/reg copy.  */
	  && can_copy_p (GET_MODE (dest))
	  /* GCSE commonly inserts instruction after the insn.  We can't
	     do that easily for EH_REGION notes so disable GCSE on these
	     for now.  */
	  && !find_reg_note (insn, REG_EH_REGION, NULL_RTX)
	  /* Is SET_SRC something we want to gcse?  */
	  && want_to_gcse_p (src)
	  /* Don't CSE a nop.  */
	  && ! set_noop_p (pat)
	  /* Don't GCSE if it has attached REG_EQUIV note.
	     At this point this only function parameters should have
	     REG_EQUIV notes and if the argument slot is used somewhere
	     explicitly, it means address of parameter has been taken,
	     so we should not extend the lifetime of the pseudo.  */
	  && (note == NULL_RTX || ! MEM_P (XEXP (note, 0))))
	{
	  /* An expression is not anticipatable if its operands are
	     modified before this insn or if this is not the only SET in
	     this insn.  */
	  int antic_p = oprs_anticipatable_p (src, insn) && single_set (insn);
	  /* An expression is not available if its operands are
	     subsequently modified, including this insn.  It's also not
	     available if this is a branch, because we can't insert
	     a set after the branch.  */
	  int avail_p = (oprs_available_p (src, insn)
			 && ! JUMP_P (insn));

	  insert_expr_in_table (src, GET_MODE (dest), insn, antic_p, avail_p, table);
	}

      /* Record sets for constant/copy propagation.  */
      else if (table->set_p
	       && regno >= FIRST_PSEUDO_REGISTER
	       && ((REG_P (src)
		    && REGNO (src) >= FIRST_PSEUDO_REGISTER
		    && can_copy_p (GET_MODE (dest))
		    && REGNO (src) != regno)
		   || gcse_constant_p (src))
	       /* A copy is not available if its src or dest is subsequently
		  modified.  Here we want to search from INSN+1 on, but
		  oprs_available_p searches from INSN on.  */
	       && (insn == BB_END (BLOCK_FOR_INSN (insn))
		   || ((tmp = next_nonnote_insn (insn)) != NULL_RTX
		       && oprs_available_p (pat, tmp))))
	insert_set_in_table (pat, insn, table);
    }
  /* In case of store we want to consider the memory value as available in
     the REG stored in that memory. This makes it possible to remove
     redundant loads from due to stores to the same location.  */
  else if (flag_gcse_las && REG_P (src) && MEM_P (dest))
      {
        unsigned int regno = REGNO (src);

        /* Do not do this for constant/copy propagation.  */
        if (! table->set_p
            /* Only record sets of pseudo-regs in the hash table.  */
	    && regno >= FIRST_PSEUDO_REGISTER
	   /* Don't GCSE something if we can't do a reg/reg copy.  */
	   && can_copy_p (GET_MODE (src))
	   /* GCSE commonly inserts instruction after the insn.  We can't
	      do that easily for EH_REGION notes so disable GCSE on these
	      for now.  */
	   && ! find_reg_note (insn, REG_EH_REGION, NULL_RTX)
	   /* Is SET_DEST something we want to gcse?  */
	   && want_to_gcse_p (dest)
	   /* Don't CSE a nop.  */
	   && ! set_noop_p (pat)
	   /* Don't GCSE if it has attached REG_EQUIV note.
	      At this point this only function parameters should have
	      REG_EQUIV notes and if the argument slot is used somewhere
	      explicitly, it means address of parameter has been taken,
	      so we should not extend the lifetime of the pseudo.  */
	   && ((note = find_reg_note (insn, REG_EQUIV, NULL_RTX)) == 0
	       || ! MEM_P (XEXP (note, 0))))
             {
               /* Stores are never anticipatable.  */
               int antic_p = 0;
	       /* An expression is not available if its operands are
	          subsequently modified, including this insn.  It's also not
	          available if this is a branch, because we can't insert
	          a set after the branch.  */
               int avail_p = oprs_available_p (dest, insn)
			     && ! JUMP_P (insn);

	       /* Record the memory expression (DEST) in the hash table.  */
	       insert_expr_in_table (dest, GET_MODE (dest), insn,
				     antic_p, avail_p, table);
             }
      }
}