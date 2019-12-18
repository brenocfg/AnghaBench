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
 int /*<<< orphan*/  GOTO_EXPR ; 
 scalar_t__ LABEL_DECL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int TREE_INT_CST_LOW (scalar_t__) ; 
 scalar_t__ add_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_may_fallthru (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ create_artificial_label () ; 
 int /*<<< orphan*/  cur_stmt_list ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  void_type_node ; 

tree
c_finish_bc_stmt (tree *label_p, bool is_break)
{
  bool skip;
  tree label = *label_p;

  /* In switch statements break is sometimes stylistically used after
     a return statement.  This can lead to spurious warnings about
     control reaching the end of a non-void function when it is
     inlined.  Note that we are calling block_may_fallthru with
     language specific tree nodes; this works because
     block_may_fallthru returns true when given something it does not
     understand.  */
  skip = !block_may_fallthru (cur_stmt_list);

  if (!label)
    {
      if (!skip)
	*label_p = label = create_artificial_label ();
    }
  else if (TREE_CODE (label) == LABEL_DECL)
    ;
  else switch (TREE_INT_CST_LOW (label))
    {
    case 0:
      if (is_break)
	error ("break statement not within loop or switch");
      else
	error ("continue statement not within a loop");
      return NULL_TREE;

    case 1:
      gcc_assert (is_break);
      error ("break statement used with OpenMP for loop");
      return NULL_TREE;

    default:
      gcc_unreachable ();
    }

  if (skip)
    return NULL_TREE;

  return add_stmt (build1 (GOTO_EXPR, void_type_node, label));
}