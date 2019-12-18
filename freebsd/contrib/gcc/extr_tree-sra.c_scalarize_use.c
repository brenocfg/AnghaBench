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
typedef  int /*<<< orphan*/ * tree ;
struct sra_elt {int /*<<< orphan*/ * replacement; } ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;

/* Variables and functions */
 int /*<<< orphan*/ * bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generate_copy_inout (struct sra_elt*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  generate_element_ref (struct sra_elt*) ; 
 int /*<<< orphan*/  mark_all_v_defs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_no_warning (struct sra_elt*) ; 
 int /*<<< orphan*/  sra_insert_after (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sra_insert_before (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_stmt (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
scalarize_use (struct sra_elt *elt, tree *expr_p, block_stmt_iterator *bsi,
	       bool is_output, bool use_all)
{
  tree list = NULL, stmt = bsi_stmt (*bsi);

  if (elt->replacement)
    {
      /* If we have a replacement, then updating the reference is as
	 simple as modifying the existing statement in place.  */
      if (is_output)
	mark_all_v_defs (stmt);
      *expr_p = elt->replacement;
      update_stmt (stmt);
    }
  else
    {
      /* Otherwise we need some copies.  If ELT is being read, then we want
	 to store all (modified) sub-elements back into the structure before
	 the reference takes place.  If ELT is being written, then we want to
	 load the changed values back into our shadow variables.  */
      /* ??? We don't check modified for reads, we just always write all of
	 the values.  We should be able to record the SSA number of the VOP
	 for which the values were last read.  If that number matches the
	 SSA number of the VOP in the current statement, then we needn't
	 emit an assignment.  This would also eliminate double writes when
	 a structure is passed as more than one argument to a function call.
	 This optimization would be most effective if sra_walk_function
	 processed the blocks in dominator order.  */

      generate_copy_inout (elt, is_output, generate_element_ref (elt), &list);
      if (list == NULL)
	return;
      mark_all_v_defs (list);
      if (is_output)
	sra_insert_after (bsi, list);
      else
	{
	  sra_insert_before (bsi, list);
	  if (use_all)
	    mark_no_warning (elt);
	}
    }
}