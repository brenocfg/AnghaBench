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
struct case_node {struct case_node* right; int /*<<< orphan*/ * left; int /*<<< orphan*/  parent; scalar_t__ code_label; void* high; void* low; } ;

/* Variables and functions */
 scalar_t__ INTEGER_CST ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_INT_CST_HIGH (scalar_t__) ; 
 int /*<<< orphan*/  TREE_INT_CST_LOW (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAX_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_MIN_VALUE (scalar_t__) ; 
 void* build_int_cst_wide (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 struct case_node* ggc_alloc (int) ; 
 scalar_t__ tree_int_cst_compare (scalar_t__,scalar_t__) ; 
 scalar_t__ tree_int_cst_equal (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct case_node *
add_case_node (struct case_node *head, tree type, tree low, tree high,
	       tree label)
{
  tree min_value, max_value;
  struct case_node *r;

  gcc_assert (TREE_CODE (low) == INTEGER_CST);
  gcc_assert (!high || TREE_CODE (high) == INTEGER_CST);

  min_value = TYPE_MIN_VALUE (type);
  max_value = TYPE_MAX_VALUE (type);

  /* If there's no HIGH value, then this is not a case range; it's
     just a simple case label.  But that's just a degenerate case
     range.
     If the bounds are equal, turn this into the one-value case.  */
  if (!high || tree_int_cst_equal (low, high))
    {
      /* If the simple case value is unreachable, ignore it.  */
      if ((TREE_CODE (min_value) == INTEGER_CST
            && tree_int_cst_compare (low, min_value) < 0)
	  || (TREE_CODE (max_value) == INTEGER_CST
	      && tree_int_cst_compare (low, max_value) > 0))
	return head;
      low = fold_convert (type, low);
      high = low;
    }
  else
    {
      /* If the entire case range is unreachable, ignore it.  */
      if ((TREE_CODE (min_value) == INTEGER_CST
            && tree_int_cst_compare (high, min_value) < 0)
	  || (TREE_CODE (max_value) == INTEGER_CST
	      && tree_int_cst_compare (low, max_value) > 0))
	return head;

      /* If the lower bound is less than the index type's minimum
	 value, truncate the range bounds.  */
      if (TREE_CODE (min_value) == INTEGER_CST
            && tree_int_cst_compare (low, min_value) < 0)
	low = min_value;
      low = fold_convert (type, low);

      /* If the upper bound is greater than the index type's maximum
	 value, truncate the range bounds.  */
      if (TREE_CODE (max_value) == INTEGER_CST
	  && tree_int_cst_compare (high, max_value) > 0)
	high = max_value;
      high = fold_convert (type, high);
    }


  /* Add this label to the chain.  Make sure to drop overflow flags.  */
  r = ggc_alloc (sizeof (struct case_node));
  r->low = build_int_cst_wide (TREE_TYPE (low), TREE_INT_CST_LOW (low),
			       TREE_INT_CST_HIGH (low));
  r->high = build_int_cst_wide (TREE_TYPE (high), TREE_INT_CST_LOW (high),
				TREE_INT_CST_HIGH (high));
  r->code_label = label;
  r->parent = r->left = NULL;
  r->right = head;
  return r;
}