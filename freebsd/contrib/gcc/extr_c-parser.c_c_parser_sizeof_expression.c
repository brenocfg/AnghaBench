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
struct c_type_name {TYPE_3__* declarator; } ;
struct c_expr {int /*<<< orphan*/  value; int /*<<< orphan*/  original_code; } ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_4__ {scalar_t__ vla_unspec_p; } ;
struct TYPE_5__ {TYPE_1__ array; } ;
struct TYPE_6__ {scalar_t__ kind; TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ COMPONENT_REF ; 
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 scalar_t__ DECL_C_BIT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_MARK ; 
 int /*<<< orphan*/  RID_SIZEOF ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 struct c_expr c_expr_sizeof_expr (struct c_expr) ; 
 struct c_expr c_expr_sizeof_type (struct c_type_name*) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_peek_2nd_token (int /*<<< orphan*/ *) ; 
 struct c_expr c_parser_postfix_expression_after_paren_type (int /*<<< orphan*/ *,struct c_type_name*) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct c_type_name* c_parser_type_name (int /*<<< orphan*/ *) ; 
 struct c_expr c_parser_unary_expression (int /*<<< orphan*/ *) ; 
 scalar_t__ c_token_starts_typename (int /*<<< orphan*/ ) ; 
 scalar_t__ cdk_array ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_sizeof ; 
 int /*<<< orphan*/  skip_evaluation ; 

__attribute__((used)) static struct c_expr
c_parser_sizeof_expression (c_parser *parser)
{
  struct c_expr expr;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_SIZEOF));
  c_parser_consume_token (parser);
  skip_evaluation++;
  in_sizeof++;
  if (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      /* Either sizeof ( type-name ) or sizeof unary-expression
	 starting with a compound literal.  */
      struct c_type_name *type_name;
      c_parser_consume_token (parser);
      type_name = c_parser_type_name (parser);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      if (type_name == NULL)
	{
	  struct c_expr ret;
	  skip_evaluation--;
	  in_sizeof--;
	  ret.value = error_mark_node;
	  ret.original_code = ERROR_MARK;
	  return ret;
	}
      if (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  expr = c_parser_postfix_expression_after_paren_type (parser,
							       type_name);
	  goto sizeof_expr;
	}
      /* sizeof ( type-name ).  */
      skip_evaluation--;
      in_sizeof--;
      if (type_name->declarator->kind == cdk_array
	  && type_name->declarator->u.array.vla_unspec_p)
	{
	  /* C99 6.7.5.2p4 */
	  error ("%<[*]%> not allowed in other than a declaration");
	}
      return c_expr_sizeof_type (type_name);
    }
  else
    {
      expr = c_parser_unary_expression (parser);
    sizeof_expr:
      skip_evaluation--;
      in_sizeof--;
      if (TREE_CODE (expr.value) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (TREE_OPERAND (expr.value, 1)))
	error ("%<sizeof%> applied to a bit-field");
      return c_expr_sizeof_expr (expr);
    }
}