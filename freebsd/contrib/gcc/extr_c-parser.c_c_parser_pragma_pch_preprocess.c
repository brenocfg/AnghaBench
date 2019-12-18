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
typedef  int /*<<< orphan*/ * tree ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_2__ {int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_STRING ; 
 int /*<<< orphan*/  TREE_STRING_POINTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_common_pch_pragma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_consume_pragma (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_skip_to_pragma_eol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_in ; 

__attribute__((used)) static void
c_parser_pragma_pch_preprocess (c_parser *parser)
{
  tree name = NULL;

  c_parser_consume_pragma (parser);
  if (c_parser_next_token_is (parser, CPP_STRING))
    {
      name = c_parser_peek_token (parser)->value;
      c_parser_consume_token (parser);
    }
  else
    c_parser_error (parser, "expected string literal");
  c_parser_skip_to_pragma_eol (parser);

  if (name)
    c_common_pch_pragma (parse_in, TREE_STRING_POINTER (name));
}