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
struct affine_tree_combination {int dummy; } ;

/* Variables and functions */
 scalar_t__ HOST_BITS_PER_WIDE_INT ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aff_combination_to_tree (struct affine_tree_combination*) ; 
 int /*<<< orphan*/  tree_to_aff_combination (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct affine_tree_combination*) ; 

__attribute__((used)) static tree
fold_affine_expr (tree expr)
{
  tree type = TREE_TYPE (expr);
  struct affine_tree_combination comb;

  if (TYPE_PRECISION (type) > HOST_BITS_PER_WIDE_INT)
    return expr;

  tree_to_aff_combination (expr, type, &comb);
  return aff_combination_to_tree (&comb);
}