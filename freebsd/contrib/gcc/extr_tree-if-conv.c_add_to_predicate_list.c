#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  TYPE_1__* basic_block ;
struct TYPE_3__ {scalar_t__ aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUTH_OR_EXPR ; 
 int /*<<< orphan*/  boolean_type_node ; 
 scalar_t__ fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  unshare_expr (scalar_t__) ; 

__attribute__((used)) static void
add_to_predicate_list (basic_block bb, tree new_cond)
{
  tree cond = bb->aux;

  if (cond)
    cond = fold_build2 (TRUTH_OR_EXPR, boolean_type_node,
			unshare_expr (cond), new_cond);
  else
    cond = new_cond;

  bb->aux = cond;
}