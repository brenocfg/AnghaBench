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
struct c_expr {void* original_code; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_2__ {int type; int /*<<< orphan*/  keyword; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EXPR ; 
 int /*<<< orphan*/  BIT_NOT_EXPR ; 
 int /*<<< orphan*/  CONVERT_EXPR ; 
#define  CPP_AND 142 
#define  CPP_AND_AND 141 
#define  CPP_COMPL 140 
#define  CPP_KEYWORD 139 
#define  CPP_MINUS 138 
#define  CPP_MINUS_MINUS 137 
#define  CPP_MULT 136 
 int /*<<< orphan*/  CPP_NAME ; 
#define  CPP_NOT 135 
#define  CPP_PLUS 134 
#define  CPP_PLUS_PLUS 133 
 void* ERROR_MARK ; 
 int /*<<< orphan*/  IMAGPART_EXPR ; 
 int /*<<< orphan*/  NEGATE_EXPR ; 
 int /*<<< orphan*/  OPT_Wtraditional ; 
 int /*<<< orphan*/  PREDECREMENT_EXPR ; 
 int /*<<< orphan*/  PREINCREMENT_EXPR ; 
 int /*<<< orphan*/  REALPART_EXPR ; 
#define  RID_ALIGNOF 132 
#define  RID_EXTENSION 131 
#define  RID_IMAGPART 130 
#define  RID_REALPART 129 
#define  RID_SIZEOF 128 
 int /*<<< orphan*/  TRUTH_NOT_EXPR ; 
 int /*<<< orphan*/  build_indirect_ref (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  c_dialect_objc () ; 
 struct c_expr c_parser_alignof_expression (int /*<<< orphan*/ *) ; 
 struct c_expr c_parser_cast_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 struct c_expr c_parser_postfix_expression (int /*<<< orphan*/ *) ; 
 struct c_expr c_parser_sizeof_expression (int /*<<< orphan*/ *) ; 
 struct c_expr default_function_array_conversion (struct c_expr) ; 
 int disable_extension_diagnostics () ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  finish_label_address_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_system_header ; 
 struct c_expr parser_build_unary_op (int /*<<< orphan*/ ,struct c_expr) ; 
 int /*<<< orphan*/  restore_extension_diagnostics (int) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct c_expr
c_parser_unary_expression (c_parser *parser)
{
  int ext;
  struct c_expr ret, op;
  switch (c_parser_peek_token (parser)->type)
    {
    case CPP_PLUS_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_cast_expression (parser, NULL);
      op = default_function_array_conversion (op);
      return parser_build_unary_op (PREINCREMENT_EXPR, op);
    case CPP_MINUS_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_cast_expression (parser, NULL);
      op = default_function_array_conversion (op);
      return parser_build_unary_op (PREDECREMENT_EXPR, op);
    case CPP_AND:
      c_parser_consume_token (parser);
      return parser_build_unary_op (ADDR_EXPR,
				    c_parser_cast_expression (parser, NULL));
    case CPP_MULT:
      c_parser_consume_token (parser);
      op = c_parser_cast_expression (parser, NULL);
      op = default_function_array_conversion (op);
      ret.value = build_indirect_ref (op.value, "unary *");
      ret.original_code = ERROR_MARK;
      return ret;
    case CPP_PLUS:
      c_parser_consume_token (parser);
      if (!c_dialect_objc () && !in_system_header)
	warning (OPT_Wtraditional,
		 "traditional C rejects the unary plus operator");
      op = c_parser_cast_expression (parser, NULL);
      op = default_function_array_conversion (op);
      return parser_build_unary_op (CONVERT_EXPR, op);
    case CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_cast_expression (parser, NULL);
      op = default_function_array_conversion (op);
      return parser_build_unary_op (NEGATE_EXPR, op);
    case CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_cast_expression (parser, NULL);
      op = default_function_array_conversion (op);
      return parser_build_unary_op (BIT_NOT_EXPR, op);
    case CPP_NOT:
      c_parser_consume_token (parser);
      op = c_parser_cast_expression (parser, NULL);
      op = default_function_array_conversion (op);
      return parser_build_unary_op (TRUTH_NOT_EXPR, op);
    case CPP_AND_AND:
      /* Refer to the address of a label as a pointer.  */
      c_parser_consume_token (parser);
      if (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ret.value = finish_label_address_expr
	    (c_parser_peek_token (parser)->value);
	  c_parser_consume_token (parser);
	}
      else
	{
	  c_parser_error (parser, "expected identifier");
	  ret.value = error_mark_node;
	}
	ret.original_code = ERROR_MARK;
	return ret;
    case CPP_KEYWORD:
      switch (c_parser_peek_token (parser)->keyword)
	{
	case RID_SIZEOF:
	  return c_parser_sizeof_expression (parser);
	case RID_ALIGNOF:
	  return c_parser_alignof_expression (parser);
	case RID_EXTENSION:
	  c_parser_consume_token (parser);
	  ext = disable_extension_diagnostics ();
	  ret = c_parser_cast_expression (parser, NULL);
	  restore_extension_diagnostics (ext);
	  return ret;
	case RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_cast_expression (parser, NULL);
	  op = default_function_array_conversion (op);
	  return parser_build_unary_op (REALPART_EXPR, op);
	case RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_cast_expression (parser, NULL);
	  op = default_function_array_conversion (op);
	  return parser_build_unary_op (IMAGPART_EXPR, op);
	default:
	  return c_parser_postfix_expression (parser);
	}
    default:
      return c_parser_postfix_expression (parser);
    }
}