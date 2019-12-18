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
 scalar_t__ CHREC_LEFT (scalar_t__) ; 
 scalar_t__ CHREC_RIGHT (scalar_t__) ; 
 int CHREC_VARIABLE (scalar_t__) ; 
 scalar_t__ POLYNOMIAL_CHREC ; 
 scalar_t__ SCALAR_FLOAT_TYPE_P (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ build_int_cst (scalar_t__,int) ; 
 scalar_t__ build_polynomial_chrec (int,scalar_t__,scalar_t__) ; 
 scalar_t__ build_real (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ chrec_fold_multiply (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ chrec_fold_plus (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ chrec_type (scalar_t__) ; 
 int /*<<< orphan*/  dconst2 ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static inline tree 
chrec_fold_multiply_poly_poly (tree type, 
			       tree poly0, 
			       tree poly1)
{
  tree t0, t1, t2;
  int var;

  gcc_assert (poly0);
  gcc_assert (poly1);
  gcc_assert (TREE_CODE (poly0) == POLYNOMIAL_CHREC);
  gcc_assert (TREE_CODE (poly1) == POLYNOMIAL_CHREC);
  gcc_assert (chrec_type (poly0) == chrec_type (poly1));
  gcc_assert (type == chrec_type (poly0));
  
  /* {a, +, b}_1 * {c, +, d}_2  ->  {c*{a, +, b}_1, +, d}_2,
     {a, +, b}_2 * {c, +, d}_1  ->  {a*{c, +, d}_1, +, b}_2,
     {a, +, b}_x * {c, +, d}_x  ->  {a*c, +, a*d + b*c + b*d, +, 2*b*d}_x.  */
  if (CHREC_VARIABLE (poly0) < CHREC_VARIABLE (poly1))
    /* poly0 is a constant wrt. poly1.  */
    return build_polynomial_chrec 
      (CHREC_VARIABLE (poly1), 
       chrec_fold_multiply (type, CHREC_LEFT (poly1), poly0),
       CHREC_RIGHT (poly1));
  
  if (CHREC_VARIABLE (poly1) < CHREC_VARIABLE (poly0))
    /* poly1 is a constant wrt. poly0.  */
    return build_polynomial_chrec 
      (CHREC_VARIABLE (poly0), 
       chrec_fold_multiply (type, CHREC_LEFT (poly0), poly1),
       CHREC_RIGHT (poly0));
  
  /* poly0 and poly1 are two polynomials in the same variable,
     {a, +, b}_x * {c, +, d}_x  ->  {a*c, +, a*d + b*c + b*d, +, 2*b*d}_x.  */
      
  /* "a*c".  */
  t0 = chrec_fold_multiply (type, CHREC_LEFT (poly0), CHREC_LEFT (poly1));

  /* "a*d + b*c + b*d".  */
  t1 = chrec_fold_multiply (type, CHREC_LEFT (poly0), CHREC_RIGHT (poly1));
  t1 = chrec_fold_plus (type, t1, chrec_fold_multiply (type,
						       CHREC_RIGHT (poly0),
						       CHREC_LEFT (poly1)));
  t1 = chrec_fold_plus (type, t1, chrec_fold_multiply (type,
						       CHREC_RIGHT (poly0),
						       CHREC_RIGHT (poly1)));
  /* "2*b*d".  */
  t2 = chrec_fold_multiply (type, CHREC_RIGHT (poly0), CHREC_RIGHT (poly1));
  t2 = chrec_fold_multiply (type, SCALAR_FLOAT_TYPE_P (type)
			    ? build_real (type, dconst2)
			    : build_int_cst (type, 2), t2);

  var = CHREC_VARIABLE (poly0);
  return build_polynomial_chrec (var, t0,
				 build_polynomial_chrec (var, t1, t2));
}