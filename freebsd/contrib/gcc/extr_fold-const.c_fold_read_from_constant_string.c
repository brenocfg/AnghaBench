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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 scalar_t__ ARRAY_REF ; 
 scalar_t__ GET_MODE_CLASS (scalar_t__) ; 
 int GET_MODE_SIZE (scalar_t__) ; 
 scalar_t__ INDIRECT_REF ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ INTEGER_TYPE ; 
 scalar_t__ MODE_INT ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ STRING_CST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 size_t TREE_INT_CST_LOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_OPERAND (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TREE_STRING_LENGTH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_STRING_POINTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_TYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ TYPE_MODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * array_ref_low_bound (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ compare_tree_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fold_convert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  integer_zerop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * size_diffop (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sizetype ; 
 int /*<<< orphan*/ * string_constant (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

tree
fold_read_from_constant_string (tree exp)
{
  if ((TREE_CODE (exp) == INDIRECT_REF
       || TREE_CODE (exp) == ARRAY_REF)
      && TREE_CODE (TREE_TYPE (exp)) == INTEGER_TYPE)
    {
      tree exp1 = TREE_OPERAND (exp, 0);
      tree index;
      tree string;

      if (TREE_CODE (exp) == INDIRECT_REF)
	string = string_constant (exp1, &index);
      else
	{
	  tree low_bound = array_ref_low_bound (exp);
	  index = fold_convert (sizetype, TREE_OPERAND (exp, 1));

	  /* Optimize the special-case of a zero lower bound.

	     We convert the low_bound to sizetype to avoid some problems
	     with constant folding.  (E.g. suppose the lower bound is 1,
	     and its mode is QI.  Without the conversion,l (ARRAY
	     +(INDEX-(unsigned char)1)) becomes ((ARRAY+(-(unsigned char)1))
	     +INDEX), which becomes (ARRAY+255+INDEX).  Opps!)  */
	  if (! integer_zerop (low_bound))
	    index = size_diffop (index, fold_convert (sizetype, low_bound));

	  string = exp1;
	}

      if (string
	  && TYPE_MODE (TREE_TYPE (exp)) == TYPE_MODE (TREE_TYPE (TREE_TYPE (string)))
	  && TREE_CODE (string) == STRING_CST
	  && TREE_CODE (index) == INTEGER_CST
	  && compare_tree_int (index, TREE_STRING_LENGTH (string)) < 0
	  && (GET_MODE_CLASS (TYPE_MODE (TREE_TYPE (TREE_TYPE (string))))
	      == MODE_INT)
	  && (GET_MODE_SIZE (TYPE_MODE (TREE_TYPE (TREE_TYPE (string)))) == 1))
	return fold_convert (TREE_TYPE (exp),
			     build_int_cst (NULL_TREE,
					    (TREE_STRING_POINTER (string)
					     [TREE_INT_CST_LOW (index)])));
    }
  return NULL;
}