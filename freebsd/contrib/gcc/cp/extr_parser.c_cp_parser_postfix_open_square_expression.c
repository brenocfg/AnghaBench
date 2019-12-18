#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_7__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_SQUARE ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_constant_expression (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_expression (TYPE_1__*,int) ; 
 scalar_t__ cp_parser_non_integral_constant_expression (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  grok_array_decl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
cp_parser_postfix_open_square_expression (cp_parser *parser,
					  tree postfix_expression,
					  bool for_offsetof)
{
  tree index;

  /* Consume the `[' token.  */
  cp_lexer_consume_token (parser->lexer);

  /* Parse the index expression.  */
  /* ??? For offsetof, there is a question of what to allow here.  If
     offsetof is not being used in an integral constant expression context,
     then we *could* get the right answer by computing the value at runtime.
     If we are in an integral constant expression context, then we might
     could accept any constant expression; hard to say without analysis.
     Rather than open the barn door too wide right away, allow only integer
     constant expressions here.  */
  if (for_offsetof)
    index = cp_parser_constant_expression (parser, false, NULL);
  else
    index = cp_parser_expression (parser, /*cast_p=*/false);

  /* Look for the closing `]'.  */
  cp_parser_require (parser, CPP_CLOSE_SQUARE, "`]'");

  /* Build the ARRAY_REF.  */
  postfix_expression = grok_array_decl (postfix_expression, index);

  /* When not doing offsetof, array references are not permitted in
     constant-expressions.  */
  if (!for_offsetof
      && (cp_parser_non_integral_constant_expression
	  (parser, "an array reference")))
    postfix_expression = error_mark_node;

  return postfix_expression;
}