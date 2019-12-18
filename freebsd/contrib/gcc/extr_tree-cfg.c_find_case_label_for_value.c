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
 int /*<<< orphan*/ * CASE_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CASE_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWITCH_LABELS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VEC_ELT (int /*<<< orphan*/ ,size_t) ; 
 size_t TREE_VEC_LENGTH (int /*<<< orphan*/ ) ; 
 int tree_int_cst_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
find_case_label_for_value (tree switch_expr, tree val)
{
  tree vec = SWITCH_LABELS (switch_expr);
  size_t low, high, n = TREE_VEC_LENGTH (vec);
  tree default_case = TREE_VEC_ELT (vec, n - 1);

  for (low = -1, high = n - 1; high - low > 1; )
    {
      size_t i = (high + low) / 2;
      tree t = TREE_VEC_ELT (vec, i);
      int cmp;

      /* Cache the result of comparing CASE_LOW and val.  */
      cmp = tree_int_cst_compare (CASE_LOW (t), val);

      if (cmp > 0)
	high = i;
      else
	low = i;

      if (CASE_HIGH (t) == NULL)
	{
	  /* A singe-valued case label.  */
	  if (cmp == 0)
	    return t;
	}
      else
	{
	  /* A case range.  We can only handle integer ranges.  */
	  if (cmp <= 0 && tree_int_cst_compare (CASE_HIGH (t), val) >= 0)
	    return t;
	}
    }

  return default_case;
}