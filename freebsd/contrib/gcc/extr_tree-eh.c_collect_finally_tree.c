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
typedef  int /*<<< orphan*/  tree_stmt_iterator ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  CATCH_BODY (int /*<<< orphan*/ ) ; 
#define  CATCH_EXPR 133 
#define  EH_FILTER_EXPR 132 
 int /*<<< orphan*/  EH_FILTER_FAILURE (int /*<<< orphan*/ ) ; 
#define  LABEL_EXPR 131 
 int /*<<< orphan*/  LABEL_EXPR_LABEL (int /*<<< orphan*/ ) ; 
#define  STATEMENT_LIST 130 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
#define  TRY_CATCH_EXPR 129 
#define  TRY_FINALLY_EXPR 128 
 int /*<<< orphan*/  record_in_finally_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
collect_finally_tree (tree t, tree region)
{
 tailrecurse:
  switch (TREE_CODE (t))
    {
    case LABEL_EXPR:
      record_in_finally_tree (LABEL_EXPR_LABEL (t), region);
      break;

    case TRY_FINALLY_EXPR:
      record_in_finally_tree (t, region);
      collect_finally_tree (TREE_OPERAND (t, 0), t);
      t = TREE_OPERAND (t, 1);
      goto tailrecurse;

    case TRY_CATCH_EXPR:
      collect_finally_tree (TREE_OPERAND (t, 0), region);
      t = TREE_OPERAND (t, 1);
      goto tailrecurse;

    case CATCH_EXPR:
      t = CATCH_BODY (t);
      goto tailrecurse;

    case EH_FILTER_EXPR:
      t = EH_FILTER_FAILURE (t);
      goto tailrecurse;

    case STATEMENT_LIST:
      {
	tree_stmt_iterator i;
	for (i = tsi_start (t); !tsi_end_p (i); tsi_next (&i))
	  collect_finally_tree (tsi_stmt (i), region);
      }
      break;

    default:
      /* A type, a decl, or some kind of statement that we're not
	 interested in.  Don't walk them.  */
      break;
    }
}