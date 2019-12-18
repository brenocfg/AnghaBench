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

/* Variables and functions */
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ build_x_compound_expr (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pedwarn (char*,char const*) ; 

tree build_x_compound_expr_from_list (tree list, const char *msg)
{
  tree expr = TREE_VALUE (list);

  if (TREE_CHAIN (list))
    {
      if (msg)
	pedwarn ("%s expression list treated as compound expression", msg);

      for (list = TREE_CHAIN (list); list; list = TREE_CHAIN (list))
	expr = build_x_compound_expr (expr, TREE_VALUE (list));
    }

  return expr;
}