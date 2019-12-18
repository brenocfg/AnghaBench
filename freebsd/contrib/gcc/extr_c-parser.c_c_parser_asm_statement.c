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
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_COLON ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  RID_ASM ; 
 int /*<<< orphan*/  RID_CONST ; 
 int /*<<< orphan*/  RID_RESTRICT ; 
 int /*<<< orphan*/  RID_VOLATILE ; 
 int /*<<< orphan*/  build_asm_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  build_asm_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int c_lex_string_translate ; 
 int /*<<< orphan*/  c_parser_asm_clobbers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_asm_operands (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  c_parser_asm_string_literal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_require (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  c_parser_skip_to_end_of_block_or_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
c_parser_asm_statement (c_parser *parser)
{
  tree quals, str, outputs, inputs, clobbers, ret;
  bool simple;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  if (c_parser_next_token_is_keyword (parser, RID_VOLATILE))
    {
      quals = c_parser_peek_token (parser)->value;
      c_parser_consume_token (parser);
    }
  else if (c_parser_next_token_is_keyword (parser, RID_CONST)
	   || c_parser_next_token_is_keyword (parser, RID_RESTRICT))
    {
      warning (0, "%E qualifier ignored on asm",
	       c_parser_peek_token (parser)->value);
      quals = NULL_TREE;
      c_parser_consume_token (parser);
    }
  else
    quals = NULL_TREE;
  /* ??? Follow the C++ parser rather than using the
     c_lex_string_translate kludge.  */
  c_lex_string_translate = 0;
  if (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      c_lex_string_translate = 1;
      return NULL_TREE;
    }
  str = c_parser_asm_string_literal (parser);
  if (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      simple = true;
      outputs = NULL_TREE;
      inputs = NULL_TREE;
      clobbers = NULL_TREE;
      goto done_asm;
    }
  if (!c_parser_require (parser, CPP_COLON, "expected %<:%> or %<)%>"))
    {
      c_lex_string_translate = 1;
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, NULL);
      return NULL_TREE;
    }
  simple = false;
  /* Parse outputs.  */
  if (c_parser_next_token_is (parser, CPP_COLON)
      || c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    outputs = NULL_TREE;
  else
    outputs = c_parser_asm_operands (parser, false);
  if (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      inputs = NULL_TREE;
      clobbers = NULL_TREE;
      goto done_asm;
    }
  if (!c_parser_require (parser, CPP_COLON, "expected %<:%> or %<)%>"))
    {
      c_lex_string_translate = 1;
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, NULL);
      return NULL_TREE;
    }
  /* Parse inputs.  */
  if (c_parser_next_token_is (parser, CPP_COLON)
      || c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    inputs = NULL_TREE;
  else
    inputs = c_parser_asm_operands (parser, true);
  if (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      clobbers = NULL_TREE;
      goto done_asm;
    }
  if (!c_parser_require (parser, CPP_COLON, "expected %<:%> or %<)%>"))
    {
      c_lex_string_translate = 1;
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, NULL);
      return NULL_TREE;
    }
  /* Parse clobbers.  */
  clobbers = c_parser_asm_clobbers (parser);
 done_asm:
  c_lex_string_translate = 1;
  if (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, NULL);
      return NULL_TREE;
    }
  if (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_to_end_of_block_or_statement (parser);
  ret = build_asm_stmt (quals, build_asm_expr (str, outputs, inputs,
					       clobbers, simple));
  return ret;
}