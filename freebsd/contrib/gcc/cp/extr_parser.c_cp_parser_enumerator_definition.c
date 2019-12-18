#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_5__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_EQ ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  build_enumerator (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_parser_constant_expression (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ cp_parser_identifier (TYPE_1__*) ; 
 scalar_t__ error_mark_node ; 

__attribute__((used)) static void
cp_parser_enumerator_definition (cp_parser* parser, tree type)
{
  tree identifier;
  tree value;

  /* Look for the identifier.  */
  identifier = cp_parser_identifier (parser);
  if (identifier == error_mark_node)
    return;

  /* If the next token is an '=', then there is an explicit value.  */
  if (cp_lexer_next_token_is (parser->lexer, CPP_EQ))
    {
      /* Consume the `=' token.  */
      cp_lexer_consume_token (parser->lexer);
      /* Parse the value.  */
      value = cp_parser_constant_expression (parser,
					     /*allow_non_constant_p=*/false,
					     NULL);
    }
  else
    value = NULL_TREE;

  /* Create the enumerator.  */
  build_enumerator (identifier, value, type);
}