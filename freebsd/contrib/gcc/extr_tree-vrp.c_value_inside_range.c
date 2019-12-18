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
struct TYPE_3__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
typedef  TYPE_1__ value_range_t ;
typedef  scalar_t__ tree ;

/* Variables and functions */
 int /*<<< orphan*/  GE_EXPR ; 
 int /*<<< orphan*/  LE_EXPR ; 
 scalar_t__ boolean_true_node ; 
 int /*<<< orphan*/  boolean_type_node ; 
 scalar_t__ fold_binary_to_constant (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_defer_overflow_warnings () ; 
 int /*<<< orphan*/  fold_undefer_and_ignore_overflow_warnings () ; 

__attribute__((used)) static inline int
value_inside_range (tree val, value_range_t *vr)
{
  tree cmp1, cmp2;

  fold_defer_overflow_warnings ();

  cmp1 = fold_binary_to_constant (GE_EXPR, boolean_type_node, val, vr->min);
  if (!cmp1)
  {
    fold_undefer_and_ignore_overflow_warnings ();
    return -2;
  }

  cmp2 = fold_binary_to_constant (LE_EXPR, boolean_type_node, val, vr->max);

  fold_undefer_and_ignore_overflow_warnings ();

  if (!cmp2)
    return -2;

  return cmp1 == boolean_true_node && cmp2 == boolean_true_node;
}