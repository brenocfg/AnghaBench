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
 int /*<<< orphan*/  CPP_COMMA ; 
 int /*<<< orphan*/  CPP_GREATER ; 
 int /*<<< orphan*/  CPP_LESS ; 
 int /*<<< orphan*/  CPP_NAME ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  build_tree_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_not (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_require (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  chainon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 

__attribute__((used)) static tree
c_parser_objc_protocol_refs (c_parser *parser)
{
  tree list = NULL_TREE;
  gcc_assert (c_parser_next_token_is (parser, CPP_LESS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  while (true)
    {
      tree id;
      if (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  break;
	}
      id = c_parser_peek_token (parser)->value;
      list = chainon (list, build_tree_list (NULL_TREE, id));
      c_parser_consume_token (parser);
      if (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      else
	break;
    }
  c_parser_require (parser, CPP_GREATER, "expected %<>%>");
  return list;
}