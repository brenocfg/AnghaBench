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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ elt_t ;

/* Variables and functions */
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ gimple_tree_hash (void const*) ; 
 int /*<<< orphan*/  operand_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gimple_tree_eq (const void *p1, const void *p2)
{
  tree t1 = ((const elt_t *) p1)->val;
  tree t2 = ((const elt_t *) p2)->val;
  enum tree_code code = TREE_CODE (t1);

  if (TREE_CODE (t2) != code
      || TREE_TYPE (t1) != TREE_TYPE (t2))
    return 0;

  if (!operand_equal_p (t1, t2, 0))
    return 0;

  /* Only allow them to compare equal if they also hash equal; otherwise
     results are nondeterminate, and we fail bootstrap comparison.  */
  gcc_assert (gimple_tree_hash (p1) == gimple_tree_hash (p2));

  return 1;
}