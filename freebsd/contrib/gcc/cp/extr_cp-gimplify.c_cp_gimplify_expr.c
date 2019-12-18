#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  enum gimplify_status { ____Placeholder_gimplify_status } gimplify_status ;
struct TYPE_2__ {int stmts_are_full_exprs_p; } ;

/* Variables and functions */
#define  AGGR_INIT_EXPR 148 
#define  BASELINK 147 
 int /*<<< orphan*/  BASELINK_FUNCTIONS (int /*<<< orphan*/ ) ; 
#define  BREAK_STMT 146 
#define  CONTINUE_STMT 145 
#define  DO_STMT 144 
#define  EH_SPEC_BLOCK 143 
#define  EMPTY_CLASS_EXPR 142 
#define  EXPR_STMT 141 
#define  FOR_STMT 140 
 int GS_ALL_DONE ; 
 int GS_OK ; 
#define  HANDLER 139 
#define  IF_STMT 138 
#define  INIT_EXPR 137 
#define  MUST_NOT_THROW_EXPR 136 
#define  OMP_FOR 135 
#define  PTRMEM_CST 134 
 scalar_t__ STATEMENT_CODE_P (int) ; 
 int STMT_IS_FULL_EXPR_P (int /*<<< orphan*/ ) ; 
#define  SWITCH_STMT 133 
#define  THROW_EXPR 132 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
#define  TRY_BLOCK 131 
#define  UNARY_PLUS_EXPR 130 
#define  USING_STMT 129 
#define  WHILE_STMT 128 
 int /*<<< orphan*/  bc_break ; 
 int /*<<< orphan*/  bc_continue ; 
 int /*<<< orphan*/  build_bc_goto (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_constructor (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build_empty_stmt () ; 
 int c_gimplify_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_gimplify_init_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cp_gimplify_omp_for (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cplus_expand_constant (int /*<<< orphan*/ ) ; 
 TYPE_1__* current_stmt_tree () ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genericize_catch_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  genericize_eh_spec_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  genericize_try_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gimplify_do_stmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gimplify_expr_stmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gimplify_for_stmt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gimplify_if_stmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gimplify_must_not_throw_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gimplify_switch_stmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gimplify_while_stmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simplify_aggr_init_expr (int /*<<< orphan*/ *) ; 
 int stmts_are_full_exprs_p () ; 

int
cp_gimplify_expr (tree *expr_p, tree *pre_p, tree *post_p)
{
  int saved_stmts_are_full_exprs_p = 0;
  enum tree_code code = TREE_CODE (*expr_p);
  enum gimplify_status ret;

  if (STATEMENT_CODE_P (code))
    {
      saved_stmts_are_full_exprs_p = stmts_are_full_exprs_p ();
      current_stmt_tree ()->stmts_are_full_exprs_p
	= STMT_IS_FULL_EXPR_P (*expr_p);
    }

  switch (code)
    {
    case PTRMEM_CST:
      *expr_p = cplus_expand_constant (*expr_p);
      ret = GS_OK;
      break;

    case AGGR_INIT_EXPR:
      simplify_aggr_init_expr (expr_p);
      ret = GS_OK;
      break;

    case THROW_EXPR:
      /* FIXME communicate throw type to backend, probably by moving
	 THROW_EXPR into ../tree.def.  */
      *expr_p = TREE_OPERAND (*expr_p, 0);
      ret = GS_OK;
      break;

    case MUST_NOT_THROW_EXPR:
      gimplify_must_not_throw_expr (expr_p, pre_p);
      ret = GS_OK;
      break;

      /* We used to do this for MODIFY_EXPR as well, but that's unsafe; the
	 LHS of an assignment might also be involved in the RHS, as in bug
	 25979.  */
    case INIT_EXPR:
      cp_gimplify_init_expr (expr_p, pre_p, post_p);
      ret = GS_OK;
      break;

    case EMPTY_CLASS_EXPR:
      /* We create an empty CONSTRUCTOR with RECORD_TYPE.  */
      *expr_p = build_constructor (TREE_TYPE (*expr_p), NULL);
      ret = GS_OK;
      break;

    case BASELINK:
      *expr_p = BASELINK_FUNCTIONS (*expr_p);
      ret = GS_OK;
      break;

    case TRY_BLOCK:
      genericize_try_block (expr_p);
      ret = GS_OK;
      break;

    case HANDLER:
      genericize_catch_block (expr_p);
      ret = GS_OK;
      break;

    case EH_SPEC_BLOCK:
      genericize_eh_spec_block (expr_p);
      ret = GS_OK;
      break;

    case USING_STMT:
      /* Just ignore for now.  Eventually we will want to pass this on to
	 the debugger.  */
      *expr_p = build_empty_stmt ();
      ret = GS_ALL_DONE;
      break;

    case IF_STMT:
      gimplify_if_stmt (expr_p);
      ret = GS_OK;
      break;

    case FOR_STMT:
      gimplify_for_stmt (expr_p, pre_p);
      ret = GS_ALL_DONE;
      break;

    case WHILE_STMT:
      gimplify_while_stmt (expr_p);
      ret = GS_ALL_DONE;
      break;

    case DO_STMT:
      gimplify_do_stmt (expr_p);
      ret = GS_ALL_DONE;
      break;

    case SWITCH_STMT:
      gimplify_switch_stmt (expr_p);
      ret = GS_ALL_DONE;
      break;

    case OMP_FOR:
      ret = cp_gimplify_omp_for (expr_p);
      break;

    case CONTINUE_STMT:
      *expr_p = build_bc_goto (bc_continue);
      ret = GS_ALL_DONE;
      break;

    case BREAK_STMT:
      *expr_p = build_bc_goto (bc_break);
      ret = GS_ALL_DONE;
      break;

    case EXPR_STMT:
      gimplify_expr_stmt (expr_p);
      ret = GS_OK;
      break;

    case UNARY_PLUS_EXPR:
      {
	tree arg = TREE_OPERAND (*expr_p, 0);
	tree type = TREE_TYPE (*expr_p);
	*expr_p = (TREE_TYPE (arg) != type) ? fold_convert (type, arg)
					    : arg;
	ret = GS_OK;
      }
      break;

    default:
      ret = c_gimplify_expr (expr_p, pre_p, post_p);
      break;
    }

  /* Restore saved state.  */
  if (STATEMENT_CODE_P (code))
    current_stmt_tree ()->stmts_are_full_exprs_p
      = saved_stmts_are_full_exprs_p;

  return ret;
}