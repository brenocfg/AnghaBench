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
 int /*<<< orphan*/  NOP_EXPR ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_modify_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_guard_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
set_guard (tree guard)
{
  tree guard_init;

  /* Set the GUARD to one.  */
  guard = get_guard_bits (guard);
  guard_init = integer_one_node;
  if (!same_type_p (TREE_TYPE (guard_init), TREE_TYPE (guard)))
    guard_init = convert (TREE_TYPE (guard), guard_init);
  return build_modify_expr (guard, NOP_EXPR, guard_init);
}