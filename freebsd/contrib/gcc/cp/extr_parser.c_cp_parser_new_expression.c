#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_14__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 int /*<<< orphan*/  CPP_OPEN_SQUARE ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  RID_NEW ; 
 scalar_t__ build_new (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_direct_new_declarator (TYPE_1__*) ; 
 scalar_t__ cp_parser_global_scope_opt (TYPE_1__*,int) ; 
 scalar_t__ cp_parser_new_initializer (TYPE_1__*) ; 
 scalar_t__ cp_parser_new_placement (TYPE_1__*) ; 
 scalar_t__ cp_parser_new_type_id (TYPE_1__*,scalar_t__*) ; 
 scalar_t__ cp_parser_non_integral_constant_expression (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  cp_parser_parse_definitely (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_require_keyword (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ cp_parser_type_id (TYPE_1__*) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  inform (char*) ; 

__attribute__((used)) static tree
cp_parser_new_expression (cp_parser* parser)
{
  bool global_scope_p;
  tree placement;
  tree type;
  tree initializer;
  tree nelts;

  /* Look for the optional `::' operator.  */
  global_scope_p
    = (cp_parser_global_scope_opt (parser,
				   /*current_scope_valid_p=*/false)
       != NULL_TREE);
  /* Look for the `new' operator.  */
  cp_parser_require_keyword (parser, RID_NEW, "`new'");
  /* There's no easy way to tell a new-placement from the
     `( type-id )' construct.  */
  cp_parser_parse_tentatively (parser);
  /* Look for a new-placement.  */
  placement = cp_parser_new_placement (parser);
  /* If that didn't work out, there's no new-placement.  */
  if (!cp_parser_parse_definitely (parser))
    placement = NULL_TREE;

  /* If the next token is a `(', then we have a parenthesized
     type-id.  */
  if (cp_lexer_next_token_is (parser->lexer, CPP_OPEN_PAREN))
    {
      /* Consume the `('.  */
      cp_lexer_consume_token (parser->lexer);
      /* Parse the type-id.  */
      type = cp_parser_type_id (parser);
      /* Look for the closing `)'.  */
      cp_parser_require (parser, CPP_CLOSE_PAREN, "`)'");
      /* There should not be a direct-new-declarator in this production,
	 but GCC used to allowed this, so we check and emit a sensible error
	 message for this case.  */
      if (cp_lexer_next_token_is (parser->lexer, CPP_OPEN_SQUARE))
	{
	  error ("array bound forbidden after parenthesized type-id");
	  inform ("try removing the parentheses around the type-id");
	  cp_parser_direct_new_declarator (parser);
	}
      nelts = NULL_TREE;
    }
  /* Otherwise, there must be a new-type-id.  */
  else
    type = cp_parser_new_type_id (parser, &nelts);

  /* If the next token is a `(', then we have a new-initializer.  */
  if (cp_lexer_next_token_is (parser->lexer, CPP_OPEN_PAREN))
    initializer = cp_parser_new_initializer (parser);
  else
    initializer = NULL_TREE;

  /* A new-expression may not appear in an integral constant
     expression.  */
  if (cp_parser_non_integral_constant_expression (parser, "`new'"))
    return error_mark_node;

  /* Create a representation of the new-expression.  */
  return build_new (placement, type, nelts, initializer, global_scope_p);
}