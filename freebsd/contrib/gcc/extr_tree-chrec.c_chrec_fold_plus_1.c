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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int /*<<< orphan*/  CHREC_LEFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHREC_RIGHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHREC_VARIABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARAM_SCEV_MAX_EXPR_SIZE ; 
 int PARAM_VALUE (int /*<<< orphan*/ ) ; 
 int PLUS_EXPR ; 
#define  POLYNOMIAL_CHREC 128 
 int /*<<< orphan*/  SCALAR_FLOAT_TYPE_P (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ automatically_generated_chrec_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  build_polynomial_chrec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_dont_know ; 
 int /*<<< orphan*/  chrec_fold_automatically_generated_operands (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_fold_minus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_fold_multiply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_fold_plus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_fold_plus_poly_poly (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dconstm1 ; 
 int /*<<< orphan*/  fold_build2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_contains_chrecs (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static tree
chrec_fold_plus_1 (enum tree_code code, tree type, 
		   tree op0, tree op1)
{
  if (automatically_generated_chrec_p (op0)
      || automatically_generated_chrec_p (op1))
    return chrec_fold_automatically_generated_operands (op0, op1);
  
  switch (TREE_CODE (op0))
    {
    case POLYNOMIAL_CHREC:
      switch (TREE_CODE (op1))
	{
	case POLYNOMIAL_CHREC:
	  return chrec_fold_plus_poly_poly (code, type, op0, op1);

	default:
	  if (code == PLUS_EXPR)
	    return build_polynomial_chrec 
	      (CHREC_VARIABLE (op0), 
	       chrec_fold_plus (type, CHREC_LEFT (op0), op1),
	       CHREC_RIGHT (op0));
	  else
	    return build_polynomial_chrec 
	      (CHREC_VARIABLE (op0), 
	       chrec_fold_minus (type, CHREC_LEFT (op0), op1),
	       CHREC_RIGHT (op0));
	}

    default:
      switch (TREE_CODE (op1))
	{
	case POLYNOMIAL_CHREC:
	  if (code == PLUS_EXPR)
	    return build_polynomial_chrec 
	      (CHREC_VARIABLE (op1), 
	       chrec_fold_plus (type, op0, CHREC_LEFT (op1)),
	       CHREC_RIGHT (op1));
	  else
	    return build_polynomial_chrec 
	      (CHREC_VARIABLE (op1), 
	       chrec_fold_minus (type, op0, CHREC_LEFT (op1)),
	       chrec_fold_multiply (type, CHREC_RIGHT (op1), 
				    SCALAR_FLOAT_TYPE_P (type)
				    ? build_real (type, dconstm1)
				    : build_int_cst_type (type, -1)));

	default:
	  {
	    int size = 0;
	    if ((tree_contains_chrecs (op0, &size)
		 || tree_contains_chrecs (op1, &size))
		&& size < PARAM_VALUE (PARAM_SCEV_MAX_EXPR_SIZE))
	      return build2 (code, type, op0, op1);
	    else if (size < PARAM_VALUE (PARAM_SCEV_MAX_EXPR_SIZE))
	      return fold_build2 (code, type,
				  fold_convert (type, op0),
				  fold_convert (type, op1));
	    else
	      return chrec_dont_know;
	  }
	}
    }
}