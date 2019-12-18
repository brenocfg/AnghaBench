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
struct rus_data {int may_branch; int may_throw; int /*<<< orphan*/ * last_goto; } ;

/* Variables and functions */
#define  ASM_EXPR 138 
#define  BIND_EXPR 137 
#define  CALL_EXPR 136 
#define  COND_EXPR 135 
#define  GOTO_EXPR 134 
 int /*<<< orphan*/  IS_EMPTY_STMT (int /*<<< orphan*/ ) ; 
#define  LABEL_EXPR 133 
#define  MODIFY_EXPR 132 
#define  RETURN_EXPR 131 
#define  STATEMENT_LIST 130 
 int const TREE_CODE (int /*<<< orphan*/ ) ; 
#define  TRY_CATCH_EXPR 129 
#define  TRY_FINALLY_EXPR 128 
 int /*<<< orphan*/  TSI_SAME_STMT ; 
 int /*<<< orphan*/  fold_stmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_call_expr_in (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notice_special_calls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_useless_stmts_bind (int /*<<< orphan*/ *,struct rus_data*) ; 
 int /*<<< orphan*/  remove_useless_stmts_cond (int /*<<< orphan*/ *,struct rus_data*) ; 
 int /*<<< orphan*/  remove_useless_stmts_goto (int /*<<< orphan*/ *,struct rus_data*) ; 
 int /*<<< orphan*/  remove_useless_stmts_label (int /*<<< orphan*/ *,struct rus_data*) ; 
 int /*<<< orphan*/  remove_useless_stmts_tc (int /*<<< orphan*/ *,struct rus_data*) ; 
 int /*<<< orphan*/  remove_useless_stmts_tf (int /*<<< orphan*/ *,struct rus_data*) ; 
 int /*<<< orphan*/  tree_could_throw_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_delink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_link_before (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tsi_stmt_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_call_expr_flags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
remove_useless_stmts_1 (tree *tp, struct rus_data *data)
{
  tree t = *tp, op;

  switch (TREE_CODE (t))
    {
    case COND_EXPR:
      remove_useless_stmts_cond (tp, data);
      break;

    case TRY_FINALLY_EXPR:
      remove_useless_stmts_tf (tp, data);
      break;

    case TRY_CATCH_EXPR:
      remove_useless_stmts_tc (tp, data);
      break;

    case BIND_EXPR:
      remove_useless_stmts_bind (tp, data);
      break;

    case GOTO_EXPR:
      remove_useless_stmts_goto (tp, data);
      break;

    case LABEL_EXPR:
      remove_useless_stmts_label (tp, data);
      break;

    case RETURN_EXPR:
      fold_stmt (tp);
      data->last_goto = NULL;
      data->may_branch = true;
      break;

    case CALL_EXPR:
      fold_stmt (tp);
      data->last_goto = NULL;
      notice_special_calls (t);
      update_call_expr_flags (t);
      if (tree_could_throw_p (t))
	data->may_throw = true;
      break;

    case MODIFY_EXPR:
      data->last_goto = NULL;
      fold_stmt (tp);
      op = get_call_expr_in (t);
      if (op)
	{
	  update_call_expr_flags (op);
	  notice_special_calls (op);
	}
      if (tree_could_throw_p (t))
	data->may_throw = true;
      break;

    case STATEMENT_LIST:
      {
	tree_stmt_iterator i = tsi_start (t);
	while (!tsi_end_p (i))
	  {
	    t = tsi_stmt (i);
	    if (IS_EMPTY_STMT (t))
	      {
		tsi_delink (&i);
		continue;
	      }

	    remove_useless_stmts_1 (tsi_stmt_ptr (i), data);

	    t = tsi_stmt (i);
	    if (TREE_CODE (t) == STATEMENT_LIST)
	      {
		tsi_link_before (&i, t, TSI_SAME_STMT);
		tsi_delink (&i);
	      }
	    else
	      tsi_next (&i);
	  }
      }
      break;
    case ASM_EXPR:
      fold_stmt (tp);
      data->last_goto = NULL;
      break;

    default:
      data->last_goto = NULL;
      break;
    }
}