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
typedef  scalar_t__ tree ;
struct c_expr {scalar_t__ value; } ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_2__ {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_CLOSE_SQUARE ; 
 int /*<<< orphan*/  CPP_COMMA ; 
 int /*<<< orphan*/  CPP_NAME ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 int /*<<< orphan*/  CPP_OPEN_SQUARE ; 
 int /*<<< orphan*/  IDENTIFIER_LENGTH (scalar_t__) ; 
 int /*<<< orphan*/  IDENTIFIER_POINTER (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ build_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ build_tree_list (scalar_t__,scalar_t__) ; 
 int c_lex_string_translate ; 
 scalar_t__ c_parser_asm_string_literal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 struct c_expr c_parser_expression (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_require (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ chainon (scalar_t__,scalar_t__) ; 
 struct c_expr default_function_array_conversion (struct c_expr) ; 

__attribute__((used)) static tree
c_parser_asm_operands (c_parser *parser, bool convert_p)
{
  tree list = NULL_TREE;
  while (true)
    {
      tree name, str;
      struct c_expr expr;
      if (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
	{
	  c_parser_consume_token (parser);
	  if (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      tree id = c_parser_peek_token (parser)->value;
	      c_parser_consume_token (parser);
	      name = build_string (IDENTIFIER_LENGTH (id),
				   IDENTIFIER_POINTER (id));
	    }
	  else
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, NULL);
	      return NULL_TREE;
	    }
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	}
      else
	name = NULL_TREE;
      str = c_parser_asm_string_literal (parser);
      if (str == NULL_TREE)
	return NULL_TREE;
      c_lex_string_translate = 1;
      if (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  c_lex_string_translate = 0;
	  return NULL_TREE;
	}
      expr = c_parser_expression (parser);
      if (convert_p)
	expr = default_function_array_conversion (expr);
      c_lex_string_translate = 0;
      if (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, NULL);
	  return NULL_TREE;
	}
      list = chainon (list, build_tree_list (build_tree_list (name, str),
					     expr.value));
      if (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      else
	break;
    }
  return list;
}