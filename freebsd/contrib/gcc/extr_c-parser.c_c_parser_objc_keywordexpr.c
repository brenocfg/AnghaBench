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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_expr_list (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static tree
c_parser_objc_keywordexpr (c_parser *parser)
{
  tree list = c_parser_expr_list (parser, true);
  if (TREE_CHAIN (list) == NULL_TREE)
    {
      /* Just return the expression, remove a level of
	 indirection.  */
      return TREE_VALUE (list);
    }
  else
    {
      /* We have a comma expression, we will collapse later.  */
      return list;
    }
}