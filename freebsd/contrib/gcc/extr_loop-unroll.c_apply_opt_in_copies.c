#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct var_to_expand {scalar_t__ insn; } ;
struct opt_info {unsigned int first_new_block; scalar_t__ insns_to_split; int /*<<< orphan*/ * loop_exit; scalar_t__ insns_with_var_to_expand; int /*<<< orphan*/ * loop_preheader; } ;
struct iv_to_split {scalar_t__ insn; } ;
typedef  scalar_t__ rtx ;
typedef  TYPE_1__* basic_block ;
struct TYPE_9__ {scalar_t__ aux; } ;

/* Variables and functions */
 TYPE_1__* BASIC_BLOCK (unsigned int) ; 
 scalar_t__ BB_END (TYPE_1__*) ; 
 scalar_t__ BB_HEAD (TYPE_1__*) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 int /*<<< orphan*/  allocate_basic_variable ; 
 int /*<<< orphan*/  combine_var_copies_in_loop_exit ; 
 unsigned int determine_split_iv_delta (size_t,unsigned int,int) ; 
 int /*<<< orphan*/  expand_var_during_unrolling (struct var_to_expand*,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__* get_bb_copy (TYPE_1__*) ; 
 TYPE_1__* get_bb_original (TYPE_1__*) ; 
 struct var_to_expand* htab_find (scalar_t__,struct var_to_expand*) ; 
 int /*<<< orphan*/  htab_traverse (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_base_initialization (struct var_to_expand*,scalar_t__) ; 
 int /*<<< orphan*/  insert_var_expansion_initialization ; 
 scalar_t__ last_basic_block ; 
 int /*<<< orphan*/  split_iv (struct var_to_expand*,scalar_t__,unsigned int) ; 

__attribute__((used)) static void
apply_opt_in_copies (struct opt_info *opt_info, 
                     unsigned n_copies, bool unrolling, 
                     bool rewrite_original_loop)
{
  unsigned i, delta;
  basic_block bb, orig_bb;
  rtx insn, orig_insn, next;
  struct iv_to_split ivts_templ, *ivts;
  struct var_to_expand ve_templ, *ves;
  
  /* Sanity check -- we need to put initialization in the original loop
     body.  */
  gcc_assert (!unrolling || rewrite_original_loop);
  
  /* Allocate the basic variables (i0).  */
  if (opt_info->insns_to_split)
    htab_traverse (opt_info->insns_to_split, allocate_basic_variable, NULL);
  
  for (i = opt_info->first_new_block; i < (unsigned) last_basic_block; i++)
    {
      bb = BASIC_BLOCK (i);
      orig_bb = get_bb_original (bb);
      
      /* bb->aux holds position in copy sequence initialized by
	 duplicate_loop_to_header_edge.  */
      delta = determine_split_iv_delta ((size_t)bb->aux, n_copies,
					unrolling);
      bb->aux = 0;
      orig_insn = BB_HEAD (orig_bb);
      for (insn = BB_HEAD (bb); insn != NEXT_INSN (BB_END (bb)); insn = next)
        {
          next = NEXT_INSN (insn);
          if (!INSN_P (insn))
            continue;
          
          while (!INSN_P (orig_insn))
            orig_insn = NEXT_INSN (orig_insn);
          
          ivts_templ.insn = orig_insn;
          ve_templ.insn = orig_insn;
          
          /* Apply splitting iv optimization.  */
          if (opt_info->insns_to_split)
            {
              ivts = htab_find (opt_info->insns_to_split, &ivts_templ);
              
              if (ivts)
                {
		  gcc_assert (GET_CODE (PATTERN (insn))
			      == GET_CODE (PATTERN (orig_insn)));
                  
                  if (!delta)
                    insert_base_initialization (ivts, insn);
                  split_iv (ivts, insn, delta);
                }
            }
          /* Apply variable expansion optimization.  */
          if (unrolling && opt_info->insns_with_var_to_expand)
            {
              ves = htab_find (opt_info->insns_with_var_to_expand, &ve_templ);
              if (ves)
                { 
		  gcc_assert (GET_CODE (PATTERN (insn))
			      == GET_CODE (PATTERN (orig_insn)));
                  expand_var_during_unrolling (ves, insn);
                }
            }
          orig_insn = NEXT_INSN (orig_insn);
        }
    }

  if (!rewrite_original_loop)
    return;
  
  /* Initialize the variable expansions in the loop preheader
     and take care of combining them at the loop exit.  */ 
  if (opt_info->insns_with_var_to_expand)
    {
      htab_traverse (opt_info->insns_with_var_to_expand, 
                     insert_var_expansion_initialization, 
                     opt_info->loop_preheader);
      htab_traverse (opt_info->insns_with_var_to_expand, 
                     combine_var_copies_in_loop_exit, 
                     opt_info->loop_exit);
    }
  
  /* Rewrite also the original loop body.  Find them as originals of the blocks
     in the last copied iteration, i.e. those that have
     get_bb_copy (get_bb_original (bb)) == bb.  */
  for (i = opt_info->first_new_block; i < (unsigned) last_basic_block; i++)
    {
      bb = BASIC_BLOCK (i);
      orig_bb = get_bb_original (bb);
      if (get_bb_copy (orig_bb) != bb)
	continue;
      
      delta = determine_split_iv_delta (0, n_copies, unrolling);
      for (orig_insn = BB_HEAD (orig_bb);
           orig_insn != NEXT_INSN (BB_END (bb));
           orig_insn = next)
        {
          next = NEXT_INSN (orig_insn);
          
          if (!INSN_P (orig_insn))
 	    continue;
          
          ivts_templ.insn = orig_insn;
          if (opt_info->insns_to_split)
            {
              ivts = htab_find (opt_info->insns_to_split, &ivts_templ);
              if (ivts)
                {
                  if (!delta)
                    insert_base_initialization (ivts, orig_insn);
                  split_iv (ivts, orig_insn, delta);
                  continue;
                }
            }
          
        }
    }
}