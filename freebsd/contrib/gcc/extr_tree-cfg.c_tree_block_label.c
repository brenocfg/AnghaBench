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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  BSI_NEW_STMT ; 
 int /*<<< orphan*/  DECL_NONLOCAL (int /*<<< orphan*/ ) ; 
 scalar_t__ LABEL_EXPR ; 
 int /*<<< orphan*/  LABEL_EXPR_LABEL (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_insert_before (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_move_before (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build1 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_artificial_label () ; 
 int /*<<< orphan*/  void_type_node ; 

tree
tree_block_label (basic_block bb)
{
  block_stmt_iterator i, s = bsi_start (bb);
  bool first = true;
  tree label, stmt;

  for (i = s; !bsi_end_p (i); first = false, bsi_next (&i))
    {
      stmt = bsi_stmt (i);
      if (TREE_CODE (stmt) != LABEL_EXPR)
	break;
      label = LABEL_EXPR_LABEL (stmt);
      if (!DECL_NONLOCAL (label))
	{
	  if (!first)
	    bsi_move_before (&i, &s);
	  return label;
	}
    }

  label = create_artificial_label ();
  stmt = build1 (LABEL_EXPR, void_type_node, label);
  bsi_insert_before (&s, stmt, BSI_NEW_STMT);
  return label;
}