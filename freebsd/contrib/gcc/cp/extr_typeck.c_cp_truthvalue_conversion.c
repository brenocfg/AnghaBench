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

/* Variables and functions */
 int /*<<< orphan*/  NE_EXPR ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PTRMEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_binary_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  c_common_truthvalue_conversion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_zero_node ; 

tree
cp_truthvalue_conversion (tree expr)
{
  tree type = TREE_TYPE (expr);
  if (TYPE_PTRMEM_P (type))
    return build_binary_op (NE_EXPR, expr, integer_zero_node, 1);
  else
    return c_common_truthvalue_conversion (expr);
}