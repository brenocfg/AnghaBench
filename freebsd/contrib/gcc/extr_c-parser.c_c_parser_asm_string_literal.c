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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_STRING ; 
 int /*<<< orphan*/  CPP_WSTRING ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  build_string (int,char*) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static tree
c_parser_asm_string_literal (c_parser *parser)
{
  tree str;
  if (c_parser_next_token_is (parser, CPP_STRING))
    {
      str = c_parser_peek_token (parser)->value;
      c_parser_consume_token (parser);
    }
  else if (c_parser_next_token_is (parser, CPP_WSTRING))
    {
      error ("wide string literal in %<asm%>");
      str = build_string (1, "");
      c_parser_consume_token (parser);
    }
  else
    {
      c_parser_error (parser, "expected string literal");
      str = NULL_TREE;
    }
  return str;
}