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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int SIZEOF_EXPR ; 
 int /*<<< orphan*/  cxx_alignof_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxx_sizeof_expr (int /*<<< orphan*/ ) ; 

tree
cxx_sizeof_or_alignof_expr (tree e, enum tree_code op)
{
  if (op == SIZEOF_EXPR)
    return cxx_sizeof_expr (e);
  else
    return cxx_alignof_expr (e);
}