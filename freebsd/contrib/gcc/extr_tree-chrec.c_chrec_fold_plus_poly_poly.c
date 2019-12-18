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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 scalar_t__ CHREC_LEFT (scalar_t__) ; 
 scalar_t__ CHREC_RIGHT (scalar_t__) ; 
 scalar_t__ CHREC_VARIABLE (scalar_t__) ; 
 int PLUS_EXPR ; 
 scalar_t__ POLYNOMIAL_CHREC ; 
 scalar_t__ SCALAR_FLOAT_TYPE_P (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  build_int_cst_type (scalar_t__,int) ; 
 scalar_t__ build_polynomial_chrec (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  build_real (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ chrec_fold_minus (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ chrec_fold_multiply (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ chrec_fold_plus (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ chrec_type (scalar_t__) ; 
 scalar_t__ chrec_zerop (scalar_t__) ; 
 int /*<<< orphan*/  dconstm1 ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static inline tree 
chrec_fold_plus_poly_poly (enum tree_code code, 
			   tree type, 
			   tree poly0, 
			   tree poly1)
{
  tree left, right;

  gcc_assert (poly0);
  gcc_assert (poly1);
  gcc_assert (TREE_CODE (poly0) == POLYNOMIAL_CHREC);
  gcc_assert (TREE_CODE (poly1) == POLYNOMIAL_CHREC);
  gcc_assert (chrec_type (poly0) == chrec_type (poly1));
  gcc_assert (type == chrec_type (poly0));
  
  /*
    {a, +, b}_1 + {c, +, d}_2  ->  {{a, +, b}_1 + c, +, d}_2,
    {a, +, b}_2 + {c, +, d}_1  ->  {{c, +, d}_1 + a, +, b}_2,
    {a, +, b}_x + {c, +, d}_x  ->  {a+c, +, b+d}_x.  */
  if (CHREC_VARIABLE (poly0) < CHREC_VARIABLE (poly1))
    {
      if (code == PLUS_EXPR)
	return build_polynomial_chrec 
	  (CHREC_VARIABLE (poly1), 
	   chrec_fold_plus (type, poly0, CHREC_LEFT (poly1)),
	   CHREC_RIGHT (poly1));
      else
	return build_polynomial_chrec 
	  (CHREC_VARIABLE (poly1), 
	   chrec_fold_minus (type, poly0, CHREC_LEFT (poly1)),
	   chrec_fold_multiply (type, CHREC_RIGHT (poly1), 
				SCALAR_FLOAT_TYPE_P (type)
				? build_real (type, dconstm1)
				: build_int_cst_type (type, -1)));
    }
  
  if (CHREC_VARIABLE (poly0) > CHREC_VARIABLE (poly1))
    {
      if (code == PLUS_EXPR)
	return build_polynomial_chrec 
	  (CHREC_VARIABLE (poly0), 
	   chrec_fold_plus (type, CHREC_LEFT (poly0), poly1),
	   CHREC_RIGHT (poly0));
      else
	return build_polynomial_chrec 
	  (CHREC_VARIABLE (poly0), 
	   chrec_fold_minus (type, CHREC_LEFT (poly0), poly1),
	   CHREC_RIGHT (poly0));
    }
  
  if (code == PLUS_EXPR)
    {
      left = chrec_fold_plus 
	(type, CHREC_LEFT (poly0), CHREC_LEFT (poly1));
      right = chrec_fold_plus 
	(type, CHREC_RIGHT (poly0), CHREC_RIGHT (poly1));
    }
  else
    {
      left = chrec_fold_minus 
	(type, CHREC_LEFT (poly0), CHREC_LEFT (poly1));
      right = chrec_fold_minus 
	(type, CHREC_RIGHT (poly0), CHREC_RIGHT (poly1));
    }

  if (chrec_zerop (right))
    return left;
  else
    return build_polynomial_chrec 
      (CHREC_VARIABLE (poly0), left, right); 
}