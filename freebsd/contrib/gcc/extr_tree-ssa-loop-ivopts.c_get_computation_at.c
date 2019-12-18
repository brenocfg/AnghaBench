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
struct loop {int dummy; } ;
struct iv_use {TYPE_1__* iv; } ;
struct iv_cand {int dummy; } ;
struct affine_tree_combination {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aff_combination_to_tree (struct affine_tree_combination*) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_computation_aff (struct loop*,struct iv_use*,struct iv_cand*,int /*<<< orphan*/ ,struct affine_tree_combination*) ; 
 int /*<<< orphan*/  unshare_aff_combination (struct affine_tree_combination*) ; 

__attribute__((used)) static tree
get_computation_at (struct loop *loop,
		    struct iv_use *use, struct iv_cand *cand, tree at)
{
  struct affine_tree_combination aff;
  tree type = TREE_TYPE (use->iv->base);

  if (!get_computation_aff (loop, use, cand, at, &aff))
    return NULL_TREE;
  unshare_aff_combination (&aff);
  return fold_convert (type, aff_combination_to_tree (&aff));
}