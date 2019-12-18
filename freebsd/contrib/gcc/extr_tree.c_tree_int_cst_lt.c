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
typedef  scalar_t__ tree ;

/* Variables and functions */
 int INT_CST_LT (scalar_t__,scalar_t__) ; 
 int INT_CST_LT_UNSIGNED (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 int tree_int_cst_sgn (scalar_t__) ; 

int
tree_int_cst_lt (tree t1, tree t2)
{
  if (t1 == t2)
    return 0;

  if (TYPE_UNSIGNED (TREE_TYPE (t1)) != TYPE_UNSIGNED (TREE_TYPE (t2)))
    {
      int t1_sgn = tree_int_cst_sgn (t1);
      int t2_sgn = tree_int_cst_sgn (t2);

      if (t1_sgn < t2_sgn)
	return 1;
      else if (t1_sgn > t2_sgn)
	return 0;
      /* Otherwise, both are non-negative, so we compare them as
	 unsigned just in case one of them would overflow a signed
	 type.  */
    }
  else if (!TYPE_UNSIGNED (TREE_TYPE (t1)))
    return INT_CST_LT (t1, t2);

  return INT_CST_LT_UNSIGNED (t1, t2);
}