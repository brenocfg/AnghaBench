#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct c_expr {void* original_code; void* value; } ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
struct TYPE_3__ {int type; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_CLOSE_SQUARE ; 
#define  CPP_DEREF 133 
#define  CPP_DOT 132 
#define  CPP_MINUS_MINUS 131 
 int /*<<< orphan*/  CPP_NAME ; 
#define  CPP_OPEN_PAREN 130 
#define  CPP_OPEN_SQUARE 129 
#define  CPP_PLUS_PLUS 128 
 void* ERROR_MARK ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  POSTDECREMENT_EXPR ; 
 int /*<<< orphan*/  POSTINCREMENT_EXPR ; 
 void* build_array_ref (void*,int /*<<< orphan*/ ) ; 
 void* build_component_ref (void*,int /*<<< orphan*/ ) ; 
 void* build_function_call (void*,int /*<<< orphan*/ ) ; 
 void* build_indirect_ref (void*,char*) ; 
 void* build_unary_op (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  c_parser_expr_list (int /*<<< orphan*/ *,int) ; 
 TYPE_2__ c_parser_expression (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct c_expr default_function_array_conversion (struct c_expr) ; 
 void* error_mark_node ; 

__attribute__((used)) static struct c_expr
c_parser_postfix_expression_after_primary (c_parser *parser,
					   struct c_expr expr)
{
  tree ident, idx, exprlist;
  while (true)
    {
      switch (c_parser_peek_token (parser)->type)
	{
	case CPP_OPEN_SQUARE:
	  /* Array reference.  */
	  c_parser_consume_token (parser);
	  idx = c_parser_expression (parser).value;
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  expr.value = build_array_ref (expr.value, idx);
	  expr.original_code = ERROR_MARK;
	  break;
	case CPP_OPEN_PAREN:
	  /* Function call.  */
	  c_parser_consume_token (parser);
	  if (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    exprlist = NULL_TREE;
	  else
	    exprlist = c_parser_expr_list (parser, true);
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  expr.value = build_function_call (expr.value, exprlist);
	  expr.original_code = ERROR_MARK;
	  break;
	case CPP_DOT:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  expr = default_function_array_conversion (expr);
	  if (c_parser_next_token_is (parser, CPP_NAME))
	    ident = c_parser_peek_token (parser)->value;
	  else
	    {
	      c_parser_error (parser, "expected identifier");
	      expr.value = error_mark_node;
	      expr.original_code = ERROR_MARK;
	      return expr;
	    }
	  c_parser_consume_token (parser);
	  expr.value = build_component_ref (expr.value, ident);
	  expr.original_code = ERROR_MARK;
	  break;
	case CPP_DEREF:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  expr = default_function_array_conversion (expr);
	  if (c_parser_next_token_is (parser, CPP_NAME))
	    ident = c_parser_peek_token (parser)->value;
	  else
	    {
	      c_parser_error (parser, "expected identifier");
	      expr.value = error_mark_node;
	      expr.original_code = ERROR_MARK;
	      return expr;
	    }
	  c_parser_consume_token (parser);
	  expr.value = build_component_ref (build_indirect_ref (expr.value,
								"->"), ident);
	  expr.original_code = ERROR_MARK;
	  break;
	case CPP_PLUS_PLUS:
	  /* Postincrement.  */
	  c_parser_consume_token (parser);
	  expr = default_function_array_conversion (expr);
	  expr.value = build_unary_op (POSTINCREMENT_EXPR, expr.value, 0);
	  expr.original_code = ERROR_MARK;
	  break;
	case CPP_MINUS_MINUS:
	  /* Postdecrement.  */
	  c_parser_consume_token (parser);
	  expr = default_function_array_conversion (expr);
	  expr.value = build_unary_op (POSTDECREMENT_EXPR, expr.value, 0);
	  expr.original_code = ERROR_MARK;
	  break;
	default:
	  return expr;
	}
    }
}