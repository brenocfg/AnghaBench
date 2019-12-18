#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_BRACE ; 
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ cp_lexer_next_token_is_not (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_statement (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_statement_seq_opt (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cp_parser_already_scoped_statement (cp_parser* parser)
{
  /* If the token is a `{', then we must take special action.  */
  if (cp_lexer_next_token_is_not (parser->lexer, CPP_OPEN_BRACE))
    cp_parser_statement (parser, NULL_TREE, false, NULL);
  else
    {
      /* Avoid calling cp_parser_compound_statement, so that we
	 don't create a new scope.  Do everything else by hand.  */
      cp_parser_require (parser, CPP_OPEN_BRACE, "`{'");
      cp_parser_statement_seq_opt (parser, NULL_TREE);
      cp_parser_require (parser, CPP_CLOSE_BRACE, "`}'");
    }
}