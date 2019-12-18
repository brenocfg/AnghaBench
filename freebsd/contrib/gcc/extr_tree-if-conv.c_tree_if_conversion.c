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
typedef  int /*<<< orphan*/  tree ;
struct loop {unsigned int num_nodes; } ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  TYPE_1__* basic_block ;
struct TYPE_9__ {int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDI_POST_DOMINATORS ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  add_to_predicate_list (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_start (TYPE_1__*) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clean_predicate_lists (struct loop*) ; 
 int /*<<< orphan*/  combine_blocks (struct loop*) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 int /*<<< orphan*/  free_dominance_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_convertible_loop_p (struct loop*,int) ; 
 TYPE_1__** ifc_bbs ; 
 TYPE_1__* single_succ (TYPE_1__*) ; 
 scalar_t__ single_succ_p (TYPE_1__*) ; 
 int /*<<< orphan*/  tree_if_convert_stmt (struct loop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
tree_if_conversion (struct loop *loop, bool for_vectorizer)
{
  basic_block bb;
  block_stmt_iterator itr;
  unsigned int i;

  ifc_bbs = NULL;

  /* if-conversion is not appropriate for all loops. First, check if loop  is
     if-convertible or not.  */
  if (!if_convertible_loop_p (loop, for_vectorizer))
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file,"-------------------------\n");
      if (ifc_bbs)
	{
	  free (ifc_bbs);
	  ifc_bbs = NULL;
	}
      free_dominance_info (CDI_POST_DOMINATORS);
      return false;
    }

  /* Do actual work now.  */
  for (i = 0; i < loop->num_nodes; i++)
    {
      tree cond;

      bb = ifc_bbs [i];

      /* Update condition using predicate list.  */
      cond = bb->aux;

      /* Process all statements in this basic block.
	 Remove conditional expression, if any, and annotate
	 destination basic block(s) appropriately.  */
      for (itr = bsi_start (bb); !bsi_end_p (itr); /* empty */)
	{
	  tree t = bsi_stmt (itr);
	  cond = tree_if_convert_stmt (loop, t, cond, &itr);
	  if (!bsi_end_p (itr))
	    bsi_next (&itr);
	}

      /* If current bb has only one successor, then consider it as an
	 unconditional goto.  */
      if (single_succ_p (bb))
	{
	  basic_block bb_n = single_succ (bb);
	  if (cond != NULL_TREE)
	    add_to_predicate_list (bb_n, cond);
	}
    }

  /* Now, all statements are if-converted and basic blocks are
     annotated appropriately. Combine all basic block into one huge
     basic block.  */
  combine_blocks (loop);

  /* clean up */
  clean_predicate_lists (loop);
  free (ifc_bbs);
  ifc_bbs = NULL;

  return true;
}