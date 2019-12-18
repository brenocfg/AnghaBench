#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_8__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_SQUARE ; 
 int /*<<< orphan*/  CPP_OPEN_SQUARE ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  RID_DELETE ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_parser_global_scope_opt (TYPE_1__*,int) ; 
 scalar_t__ cp_parser_non_integral_constant_expression (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_require_keyword (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_simple_cast_expression (TYPE_1__*) ; 
 int /*<<< orphan*/  delete_sanity (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  error_mark_node ; 

__attribute__((used)) static tree
cp_parser_delete_expression (cp_parser* parser)
{
  bool global_scope_p;
  bool array_p;
  tree expression;

  /* Look for the optional `::' operator.  */
  global_scope_p
    = (cp_parser_global_scope_opt (parser,
				   /*current_scope_valid_p=*/false)
       != NULL_TREE);
  /* Look for the `delete' keyword.  */
  cp_parser_require_keyword (parser, RID_DELETE, "`delete'");
  /* See if the array syntax is in use.  */
  if (cp_lexer_next_token_is (parser->lexer, CPP_OPEN_SQUARE))
    {
      /* Consume the `[' token.  */
      cp_lexer_consume_token (parser->lexer);
      /* Look for the `]' token.  */
      cp_parser_require (parser, CPP_CLOSE_SQUARE, "`]'");
      /* Remember that this is the `[]' construct.  */
      array_p = true;
    }
  else
    array_p = false;

  /* Parse the cast-expression.  */
  expression = cp_parser_simple_cast_expression (parser);

  /* A delete-expression may not appear in an integral constant
     expression.  */
  if (cp_parser_non_integral_constant_expression (parser, "`delete'"))
    return error_mark_node;

  return delete_sanity (expression, NULL_TREE, array_p, global_scope_p);
}