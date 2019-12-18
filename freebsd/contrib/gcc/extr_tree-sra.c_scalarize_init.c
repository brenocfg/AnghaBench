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
struct sra_elt {scalar_t__ use_block_copy; } ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  append_to_statement_list (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generate_copy_inout (struct sra_elt*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int generate_element_init (struct sra_elt*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  generate_element_ref (struct sra_elt*) ; 
 int /*<<< orphan*/  generate_element_zero (struct sra_elt*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mark_all_v_defs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sra_insert_after (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sra_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * unshare_expr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
scalarize_init (struct sra_elt *lhs_elt, tree rhs, block_stmt_iterator *bsi)
{
  bool result = true;
  tree list = NULL;

  /* Generate initialization statements for all members extant in the RHS.  */
  if (rhs)
    {
      /* Unshare the expression just in case this is from a decl's initial.  */
      rhs = unshare_expr (rhs);
      result = generate_element_init (lhs_elt, rhs, &list);
    }

  /* CONSTRUCTOR is defined such that any member not mentioned is assigned
     a zero value.  Initialize the rest of the instantiated elements.  */
  generate_element_zero (lhs_elt, &list);

  if (!result)
    {
      /* If we failed to convert the entire initializer, then we must
	 leave the structure assignment in place and must load values
	 from the structure into the slots for which we did not find
	 constants.  The easiest way to do this is to generate a complete
	 copy-out, and then follow that with the constant assignments
	 that we were able to build.  DCE will clean things up.  */
      tree list0 = NULL;
      generate_copy_inout (lhs_elt, true, generate_element_ref (lhs_elt),
			   &list0);
      append_to_statement_list (list, &list0);
      list = list0;
    }

  if (lhs_elt->use_block_copy || !result)
    {
      /* Since LHS is not fully instantiated, we must leave the structure
	 assignment in place.  Treating this case differently from a USE
	 exposes constants to later optimizations.  */
      if (list)
	{
	  mark_all_v_defs (list);
	  sra_insert_after (bsi, list);
	}
    }
  else
    {
      /* The LHS is fully instantiated.  The list of initializations
	 replaces the original structure assignment.  */
      gcc_assert (list);
      mark_all_v_defs (bsi_stmt (*bsi));
      mark_all_v_defs (list);
      sra_replace (bsi, list);
    }
}