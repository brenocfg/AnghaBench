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
 int /*<<< orphan*/  CPP_COLON ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  build_tree_list (scalar_t__,scalar_t__) ; 
 scalar_t__ c_parser_next_token_is_not (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_objc_keywordexpr (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_objc_selector (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_require (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ chainon (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
c_parser_objc_message_args (c_parser *parser)
{
  tree sel = c_parser_objc_selector (parser);
  tree list = NULL_TREE;
  if (sel && c_parser_next_token_is_not (parser, CPP_COLON))
    return sel;
  while (true)
    {
      tree keywordexpr;
      if (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	return list;
      keywordexpr = c_parser_objc_keywordexpr (parser);
      list = chainon (list, build_tree_list (sel, keywordexpr));
      sel = c_parser_objc_selector (parser);
      if (!sel && c_parser_next_token_is_not (parser, CPP_COLON))
	break;
    }
  return list;
}