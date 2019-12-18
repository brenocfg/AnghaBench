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
struct c_type_name {TYPE_1__* specs; } ;
struct c_expr {void* original_code; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 void* ERROR_MARK ; 
 int /*<<< orphan*/  c_cast_expr (struct c_type_name*,int /*<<< orphan*/ ) ; 
 scalar_t__ c_dialect_objc () ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_peek_2nd_token (int /*<<< orphan*/ *) ; 
 struct c_expr c_parser_postfix_expression_after_paren_type (int /*<<< orphan*/ *,struct c_type_name*) ; 
 struct c_expr c_parser_postfix_expression_after_primary (int /*<<< orphan*/ *,struct c_expr) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct c_type_name* c_parser_type_name (int /*<<< orphan*/ *) ; 
 struct c_expr c_parser_unary_expression (int /*<<< orphan*/ *) ; 
 scalar_t__ c_token_starts_typename (int /*<<< orphan*/ ) ; 
 struct c_expr default_function_array_conversion (struct c_expr) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  used_types_insert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct c_expr
c_parser_cast_expression (c_parser *parser, struct c_expr *after)
{
  gcc_assert (!after || c_dialect_objc ());
  if (after)
    return c_parser_postfix_expression_after_primary (parser, *after);
  /* If the expression begins with a parenthesized type name, it may
     be either a cast or a compound literal; we need to see whether
     the next character is '{' to tell the difference.  If not, it is
     an unary expression.  */
  if (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      struct c_type_name *type_name;
      struct c_expr ret;
      struct c_expr expr;
      c_parser_consume_token (parser);
      type_name = c_parser_type_name (parser);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      if (type_name == NULL)
	{
	  ret.value = error_mark_node;
	  ret.original_code = ERROR_MARK;
	  return ret;
	}

      /* Save casted types in the function's used types hash table.  */
      used_types_insert (type_name->specs->type);

      if (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	return c_parser_postfix_expression_after_paren_type (parser,
							     type_name);
      expr = c_parser_cast_expression (parser, NULL);
      expr = default_function_array_conversion (expr);
      ret.value = c_cast_expr (type_name, expr.value);
      ret.original_code = ERROR_MARK;
      return ret;
    }
  else
    return c_parser_unary_expression (parser);
}