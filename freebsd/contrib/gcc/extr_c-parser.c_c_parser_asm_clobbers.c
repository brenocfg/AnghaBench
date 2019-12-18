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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_COMMA ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ c_parser_asm_string_literal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ tree_cons (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static tree
c_parser_asm_clobbers (c_parser *parser)
{
  tree list = NULL_TREE;
  while (true)
    {
      tree str = c_parser_asm_string_literal (parser);
      if (str)
	list = tree_cons (NULL_TREE, str, list);
      else
	return NULL_TREE;
      if (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      else
	break;
    }
  return list;
}