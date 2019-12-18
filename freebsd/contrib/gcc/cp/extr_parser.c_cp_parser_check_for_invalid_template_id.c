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
typedef  int /*<<< orphan*/  tree ;
typedef  scalar_t__ cp_token_position ;
struct TYPE_5__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_LESS ; 
 scalar_t__ IDENTIFIER_NODE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_purge_tokens_after (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ cp_lexer_token_position (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cp_parser_enclosed_template_argument_list (TYPE_1__*) ; 
 scalar_t__ cp_parser_uncommitted_to_tentative_parse_p (TYPE_1__*) ; 
 int /*<<< orphan*/  error (char*,...) ; 

__attribute__((used)) static void
cp_parser_check_for_invalid_template_id (cp_parser* parser,
					 tree type)
{
  cp_token_position start = 0;

  if (cp_lexer_next_token_is (parser->lexer, CPP_LESS))
    {
      if (TYPE_P (type))
	error ("%qT is not a template", type);
      else if (TREE_CODE (type) == IDENTIFIER_NODE)
	error ("%qE is not a template", type);
      else
	error ("invalid template-id");
      /* Remember the location of the invalid "<".  */
      if (cp_parser_uncommitted_to_tentative_parse_p (parser))
	start = cp_lexer_token_position (parser->lexer, true);
      /* Consume the "<".  */
      cp_lexer_consume_token (parser->lexer);
      /* Parse the template arguments.  */
      cp_parser_enclosed_template_argument_list (parser);
      /* Permanently remove the invalid template arguments so that
	 this error message is not issued again.  */
      if (start)
	cp_lexer_purge_tokens_after (parser->lexer, start);
    }
}