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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ COMPOUND_LITERAL_P (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 int building_stmt_tree () ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  expand_default_init (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  finish_expr_stmt (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ store_init_value (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
expand_aggr_init_1 (tree binfo, tree true_exp, tree exp, tree init, int flags)
{
  tree type = TREE_TYPE (exp);

  gcc_assert (init != error_mark_node && type != error_mark_node);
  gcc_assert (building_stmt_tree ());

  /* Use a function returning the desired type to initialize EXP for us.
     If the function is a constructor, and its first argument is
     NULL_TREE, know that it was meant for us--just slide exp on
     in and expand the constructor.  Constructors now come
     as TARGET_EXPRs.  */

  if (init && TREE_CODE (exp) == VAR_DECL
      && COMPOUND_LITERAL_P (init))
    {
      /* If store_init_value returns NULL_TREE, the INIT has been
	 recorded as the DECL_INITIAL for EXP.  That means there's
	 nothing more we have to do.  */
      init = store_init_value (exp, init);
      if (init)
	finish_expr_stmt (init);
      return;
    }

  /* We know that expand_default_init can handle everything we want
     at this point.  */
  expand_default_init (binfo, true_exp, exp, init, flags);
}