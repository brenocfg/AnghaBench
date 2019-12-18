#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  location_t ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_6__ {scalar_t__ value; } ;
struct TYPE_5__ {scalar_t__ value; } ;
struct TYPE_4__ {int type; int /*<<< orphan*/  value; int /*<<< orphan*/  keyword; int /*<<< orphan*/  location; } ;

/* Variables and functions */
 scalar_t__ BLOCK_POINTER_TYPE ; 
#define  CPP_CLOSE_PAREN 146 
#define  CPP_CLOSE_SQUARE 145 
#define  CPP_KEYWORD 144 
 int CPP_MULT ; 
 int CPP_NAME ; 
#define  CPP_OPEN_BRACE 143 
#define  CPP_PRAGMA 142 
#define  CPP_SEMICOLON 141 
 scalar_t__ EXPR_P (scalar_t__) ; 
 scalar_t__ MODIFY_EXPR ; 
 scalar_t__ NULL_TREE ; 
#define  RID_ASM 140 
#define  RID_AT_SYNCHRONIZED 139 
#define  RID_AT_THROW 138 
#define  RID_AT_TRY 137 
#define  RID_BREAK 136 
#define  RID_CONTINUE 135 
#define  RID_DO 134 
#define  RID_FOR 133 
#define  RID_GOTO 132 
#define  RID_IF 131 
#define  RID_RETURN 130 
#define  RID_SWITCH 129 
#define  RID_WHILE 128 
 int /*<<< orphan*/  SET_EXPR_LOCATION (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_break_label ; 
 int /*<<< orphan*/  c_cont_label ; 
 int /*<<< orphan*/  c_dialect_objc () ; 
 scalar_t__ c_finish_bc_stmt (int /*<<< orphan*/ *,int) ; 
 scalar_t__ c_finish_expr_stmt (scalar_t__) ; 
 scalar_t__ c_finish_goto_label (int /*<<< orphan*/ ) ; 
 scalar_t__ c_finish_goto_ptr (scalar_t__) ; 
 scalar_t__ c_finish_return (scalar_t__) ; 
 scalar_t__ c_parser_asm_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_compound_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_do_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 TYPE_3__ c_parser_expression (int /*<<< orphan*/ *) ; 
 TYPE_2__ c_parser_expression_conv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_for_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_if_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_next_token_is (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  c_parser_objc_synchronized_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_objc_try_catch_statement (int /*<<< orphan*/ *) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_pragma (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int const,char*) ; 
 int /*<<< orphan*/  c_parser_switch_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_while_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cur_block ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_location ; 
 scalar_t__ objc_build_throw_stmt (scalar_t__) ; 
 int /*<<< orphan*/  pragma_stmt ; 

__attribute__((used)) static void
c_parser_statement_after_labels (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  tree stmt = NULL_TREE;
  switch (c_parser_peek_token (parser)->type)
    {
    case CPP_OPEN_BRACE:
      add_stmt (c_parser_compound_statement (parser));
      break;
    case CPP_KEYWORD:
      switch (c_parser_peek_token (parser)->keyword)
	{
	case RID_IF:
	  c_parser_if_statement (parser);
	  break;
	case RID_SWITCH:
	  c_parser_switch_statement (parser);
	  break;
	case RID_WHILE:
	  c_parser_while_statement (parser);
	  break;
	case RID_DO:
	  c_parser_do_statement (parser);
	  break;
	case RID_FOR:
	  c_parser_for_statement (parser);
	  break;
	case RID_GOTO:
	   /* APPLE LOCAL begin radar 5732232 - blocks (C++ cb) */
	   if (cur_block)
	     error ("goto not allowed in block literal");
	   /* APPLE LOCAL end radar 5732232 - blocks (C++ cb) */
	  c_parser_consume_token (parser);
	  if (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      stmt = c_finish_goto_label (c_parser_peek_token (parser)->value);
	      c_parser_consume_token (parser);
	    }
	  else if (c_parser_next_token_is (parser, CPP_MULT))
	    {
	      c_parser_consume_token (parser);
	      stmt = c_finish_goto_ptr (c_parser_expression (parser).value);
	    }
	  else
	    c_parser_error (parser, "expected identifier or %<*%>");
	  goto expect_semicolon;
	case RID_CONTINUE:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (&c_cont_label, false);
	  goto expect_semicolon;
	case RID_BREAK:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (&c_break_label, true);
	  goto expect_semicolon;
	case RID_RETURN:
	  c_parser_consume_token (parser);
	  if (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = c_finish_return (NULL_TREE);
	      c_parser_consume_token (parser);
	    }
	  else
	    {
	      stmt = c_finish_return (c_parser_expression_conv (parser).value);
	      goto expect_semicolon;
	    }
	  break;
	case RID_ASM:
	  stmt = c_parser_asm_statement (parser);
	  break;
	case RID_AT_THROW:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  if (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = objc_build_throw_stmt (NULL_TREE);
	      c_parser_consume_token (parser);
	    }
	  else
	    {
	      stmt
		= objc_build_throw_stmt (c_parser_expression (parser).value);
	      goto expect_semicolon;
	    }
	  break;
	case RID_AT_TRY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_try_catch_statement (parser);
	  break;
	case RID_AT_SYNCHRONIZED:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_synchronized_statement (parser);
	  break;
	default:
	  goto expr_stmt;
	}
      break;
    case CPP_SEMICOLON:
      c_parser_consume_token (parser);
      break;
    case CPP_CLOSE_PAREN:
    case CPP_CLOSE_SQUARE:
      /* Avoid infinite loop in error recovery:
	 c_parser_skip_until_found stops at a closing nesting
	 delimiter without consuming it, but here we need to consume
	 it to proceed further.  */
      c_parser_error (parser, "expected statement");
      c_parser_consume_token (parser);
      break;
    case CPP_PRAGMA:
      c_parser_pragma (parser, pragma_stmt);
      break;
    default:
    expr_stmt:
      stmt = c_finish_expr_stmt (c_parser_expression_conv (parser).value);
    expect_semicolon:
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      break;
    }
  /* Two cases cannot and do not have line numbers associated: If stmt
     is degenerate, such as "2;", then stmt is an INTEGER_CST, which
     cannot hold line numbers.  But that's OK because the statement
     will either be changed to a MODIFY_EXPR during gimplification of
     the statement expr, or discarded.  If stmt was compound, but
     without new variables, we will have skipped the creation of a
     BIND and will have a bare STATEMENT_LIST.  But that's OK because
     (recursively) all of the component statements should already have
     line numbers assigned.  ??? Can we discard no-op statements
     earlier?  */
  /* APPLE LOCAL begin Radar 6144634  */
  /* Normal expr stmts, including modify exprs, get the location where
     the statement began, i.e. 'loc'.  Assignments of Blocks to Block
     pointer variables get the location of the end of the Block definition,
     i.e. 'input_location', which should already be set by this point.  */
  if (stmt && EXPR_P (stmt))
    {
      if (TREE_CODE (stmt) == MODIFY_EXPR
	  && TREE_CODE (TREE_TYPE (TREE_OPERAND (stmt, 0))) == BLOCK_POINTER_TYPE)
	SET_EXPR_LOCATION (stmt, input_location);
      else
	SET_EXPR_LOCATION (stmt, loc);
    }
  /* APPLE LOCAL end Radar 6144634  */
}