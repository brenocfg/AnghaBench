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
typedef  enum prediction { ____Placeholder_prediction } prediction ;
typedef  enum br_predictor { ____Placeholder_br_predictor } br_predictor ;

/* Variables and functions */
 scalar_t__ INTEGER_CST ; 
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 int NOT_TAKEN ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 int PRED_NEGATIVE_RETURN ; 
 int PRED_NO_PREDICTION ; 
 int PRED_NULL_RETURN ; 
 int TAKEN ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CONSTANT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_onep (int /*<<< orphan*/ ) ; 
 scalar_t__ integer_zerop (int /*<<< orphan*/ ) ; 
 scalar_t__ tree_int_cst_sgn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum br_predictor
return_prediction (tree val, enum prediction *prediction)
{
  /* VOID.  */
  if (!val)
    return PRED_NO_PREDICTION;
  /* Different heuristics for pointers and scalars.  */
  if (POINTER_TYPE_P (TREE_TYPE (val)))
    {
      /* NULL is usually not returned.  */
      if (integer_zerop (val))
	{
	  *prediction = NOT_TAKEN;
	  return PRED_NULL_RETURN;
	}
    }
  else if (INTEGRAL_TYPE_P (TREE_TYPE (val)))
    {
      /* Negative return values are often used to indicate
         errors.  */
      if (TREE_CODE (val) == INTEGER_CST
	  && tree_int_cst_sgn (val) < 0)
	{
	  *prediction = NOT_TAKEN;
	  return PRED_NEGATIVE_RETURN;
	}
      /* Constant return values seems to be commonly taken.
         Zero/one often represent booleans so exclude them from the
	 heuristics.  */
      if (TREE_CONSTANT (val)
	  && (!integer_zerop (val) && !integer_onep (val)))
	{
	  *prediction = TAKEN;
	  return PRED_NEGATIVE_RETURN;
	}
    }
  return PRED_NO_PREDICTION;
}