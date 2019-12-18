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
struct c_type_name {int dummy; } ;
struct c_expr {void* original_code; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 void* ERROR_MARK ; 
 int /*<<< orphan*/  RID_ALIGNOF ; 
 int /*<<< orphan*/  c_alignof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_alignof_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_peek_2nd_token (int /*<<< orphan*/ *) ; 
 struct c_expr c_parser_postfix_expression_after_paren_type (int /*<<< orphan*/ *,struct c_type_name*) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct c_type_name* c_parser_type_name (int /*<<< orphan*/ *) ; 
 struct c_expr c_parser_unary_expression (int /*<<< orphan*/ *) ; 
 scalar_t__ c_token_starts_typename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  groktypename (struct c_type_name*) ; 
 int /*<<< orphan*/  in_alignof ; 
 int /*<<< orphan*/  skip_evaluation ; 

__attribute__((used)) static struct c_expr
c_parser_alignof_expression (c_parser *parser)
{
  struct c_expr expr;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ALIGNOF));
  c_parser_consume_token (parser);
  skip_evaluation++;
  in_alignof++;
  if (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      /* Either __alignof__ ( type-name ) or __alignof__
	 unary-expression starting with a compound literal.  */
      struct c_type_name *type_name;
      struct c_expr ret;
      c_parser_consume_token (parser);
      type_name = c_parser_type_name (parser);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      if (type_name == NULL)
	{
	  struct c_expr ret;
	  skip_evaluation--;
	  in_alignof--;
	  ret.value = error_mark_node;
	  ret.original_code = ERROR_MARK;
	  return ret;
	}
      if (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  expr = c_parser_postfix_expression_after_paren_type (parser,
							       type_name);
	  goto alignof_expr;
	}
      /* alignof ( type-name ).  */
      skip_evaluation--;
      in_alignof--;
      ret.value = c_alignof (groktypename (type_name));
      ret.original_code = ERROR_MARK;
      return ret;
    }
  else
    {
      struct c_expr ret;
      expr = c_parser_unary_expression (parser);
    alignof_expr:
      skip_evaluation--;
      in_alignof--;
      ret.value = c_alignof_expr (expr.value);
      ret.original_code = ERROR_MARK;
      return ret;
    }
}