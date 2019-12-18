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
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 int /*<<< orphan*/  CPP_PRAGMA_EOL ; 
 int /*<<< orphan*/  c_finish_omp_flush () ; 
 int /*<<< orphan*/  c_parser_consume_pragma (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_not (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_omp_var_list_parens (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_skip_to_pragma_eol (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
c_parser_omp_flush (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  if (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    c_parser_omp_var_list_parens (parser, 0, NULL);
  else if (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    c_parser_error (parser, "expected %<(%> or end of line");
  c_parser_skip_to_pragma_eol (parser);

  c_finish_omp_flush ();
}