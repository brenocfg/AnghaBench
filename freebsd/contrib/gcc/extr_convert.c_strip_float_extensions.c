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
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 scalar_t__ CONVERT_EXPR ; 
 int /*<<< orphan*/  FLOAT_TYPE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ NOP_EXPR ; 
 scalar_t__ REAL_CST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_OPERAND (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_REAL_CST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ *) ; 
 scalar_t__ TYPE_PRECISION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_real (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * double_type_node ; 
 scalar_t__ exact_real_truncate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * float_type_node ; 
 int /*<<< orphan*/  real_value_truncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
strip_float_extensions (tree exp)
{
  tree sub, expt, subt;

  /*  For floating point constant look up the narrowest type that can hold
      it properly and handle it like (type)(narrowest_type)constant.
      This way we can optimize for instance a=a*2.0 where "a" is float
      but 2.0 is double constant.  */
  if (TREE_CODE (exp) == REAL_CST)
    {
      REAL_VALUE_TYPE orig;
      tree type = NULL;

      orig = TREE_REAL_CST (exp);
      if (TYPE_PRECISION (TREE_TYPE (exp)) > TYPE_PRECISION (float_type_node)
	  && exact_real_truncate (TYPE_MODE (float_type_node), &orig))
	type = float_type_node;
      else if (TYPE_PRECISION (TREE_TYPE (exp))
	       > TYPE_PRECISION (double_type_node)
	       && exact_real_truncate (TYPE_MODE (double_type_node), &orig))
	type = double_type_node;
      if (type)
	return build_real (type, real_value_truncate (TYPE_MODE (type), orig));
    }

  if (TREE_CODE (exp) != NOP_EXPR
      && TREE_CODE (exp) != CONVERT_EXPR)
    return exp;

  sub = TREE_OPERAND (exp, 0);
  subt = TREE_TYPE (sub);
  expt = TREE_TYPE (exp);

  if (!FLOAT_TYPE_P (subt))
    return exp;

  if (TYPE_PRECISION (subt) > TYPE_PRECISION (expt))
    return exp;

  return strip_float_extensions (sub);
}