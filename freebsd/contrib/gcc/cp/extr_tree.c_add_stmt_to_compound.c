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
 int /*<<< orphan*/  COMPOUND_EXPR ; 
 int /*<<< orphan*/  TREE_SIDE_EFFECTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_type_node ; 

tree
add_stmt_to_compound (tree orig, tree new)
{
  if (!new || !TREE_SIDE_EFFECTS (new))
    return orig;
  if (!orig || !TREE_SIDE_EFFECTS (orig))
    return new;
  return build2 (COMPOUND_EXPR, void_type_node, orig, new);
}