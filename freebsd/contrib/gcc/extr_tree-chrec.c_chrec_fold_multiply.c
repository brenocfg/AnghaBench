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
typedef  void* tree ;

/* Variables and functions */
 void* CHREC_LEFT (void*) ; 
 void* CHREC_RIGHT (void*) ; 
 int /*<<< orphan*/  CHREC_VARIABLE (void*) ; 
 int /*<<< orphan*/  MULT_EXPR ; 
#define  POLYNOMIAL_CHREC 128 
 int TREE_CODE (void*) ; 
 scalar_t__ automatically_generated_chrec_p (void*) ; 
 void* build_int_cst (void*,int /*<<< orphan*/ ) ; 
 void* build_polynomial_chrec (int /*<<< orphan*/ ,void*,void*) ; 
 void* chrec_fold_automatically_generated_operands (void*,void*) ; 
 void* chrec_fold_multiply_poly_poly (void*,void*,void*) ; 
 void* fold_build2 (int /*<<< orphan*/ ,void*,void*,void*) ; 
 int /*<<< orphan*/  integer_onep (void*) ; 
 int /*<<< orphan*/  integer_zerop (void*) ; 

tree
chrec_fold_multiply (tree type, 
		     tree op0,
		     tree op1)
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
	  return chrec_fold_multiply_poly_poly (type, op0, op1);
	  
	default:
	  if (integer_onep (op1))
	    return op0;
	  if (integer_zerop (op1))
	    return build_int_cst (type, 0);
	  
	  return build_polynomial_chrec 
	    (CHREC_VARIABLE (op0), 
	     chrec_fold_multiply (type, CHREC_LEFT (op0), op1),
	     chrec_fold_multiply (type, CHREC_RIGHT (op0), op1));
	}
      
    default:
      if (integer_onep (op0))
	return op1;
      
      if (integer_zerop (op0))
    	return build_int_cst (type, 0);
      
      switch (TREE_CODE (op1))
	{
	case POLYNOMIAL_CHREC:
	  return build_polynomial_chrec 
	    (CHREC_VARIABLE (op1), 
	     chrec_fold_multiply (type, CHREC_LEFT (op1), op0),
	     chrec_fold_multiply (type, CHREC_RIGHT (op1), op0));
	  
	default:
	  if (integer_onep (op1))
	    return op0;
	  if (integer_zerop (op1))
	    return build_int_cst (type, 0);
	  return fold_build2 (MULT_EXPR, type, op0, op1);
	}
    }
}