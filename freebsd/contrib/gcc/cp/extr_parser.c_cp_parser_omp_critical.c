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
typedef  int /*<<< orphan*/ * tree ;
typedef  int /*<<< orphan*/  cp_token ;
struct TYPE_8__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 int /*<<< orphan*/ * c_finish_omp_critical (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cp_parser_identifier (TYPE_1__*) ; 
 int /*<<< orphan*/ * cp_parser_omp_structured_block (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_require_pragma_eol (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_skip_to_closing_parenthesis (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/ * error_mark_node ; 

__attribute__((used)) static tree
cp_parser_omp_critical (cp_parser *parser, cp_token *pragma_tok)
{
  tree stmt, name = NULL;

  if (cp_lexer_next_token_is (parser->lexer, CPP_OPEN_PAREN))
    {
      cp_lexer_consume_token (parser->lexer);

      name = cp_parser_identifier (parser);

      if (name == error_mark_node
	  || !cp_parser_require (parser, CPP_CLOSE_PAREN, "`)'"))
	cp_parser_skip_to_closing_parenthesis (parser, /*recovering=*/true,
					       /*or_comma=*/false,
					       /*consume_paren=*/true);
      if (name == error_mark_node)
	name = NULL;
    }
  cp_parser_require_pragma_eol (parser, pragma_tok);

  stmt = cp_parser_omp_structured_block (parser);
  return c_finish_omp_critical (stmt, name);
}