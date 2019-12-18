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
struct iv_cand {TYPE_1__* iv; } ;
struct TYPE_2__ {int /*<<< orphan*/  step; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iv_value (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stmt_after_increment (struct loop*,struct iv_cand*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
cand_value_at (struct loop *loop, struct iv_cand *cand, tree at, tree niter)
{
  tree val = iv_value (cand->iv, niter);
  tree type = TREE_TYPE (cand->iv->base);

  if (stmt_after_increment (loop, cand, at))
    val = fold_build2 (PLUS_EXPR, type, val, cand->iv->step);

  return val;
}