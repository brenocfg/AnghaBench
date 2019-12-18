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
typedef  int /*<<< orphan*/  cp_token ;
struct TYPE_5__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_omp_var_list (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_require_pragma_eol (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_omp_flush () ; 

__attribute__((used)) static void
cp_parser_omp_flush (cp_parser *parser, cp_token *pragma_tok)
{
  if (cp_lexer_next_token_is (parser->lexer, CPP_OPEN_PAREN))
    (void) cp_parser_omp_var_list (parser, 0, NULL);
  cp_parser_require_pragma_eol (parser, pragma_tok);

  finish_omp_flush ();
}