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
 int /*<<< orphan*/  CHREC_LEFT (scalar_t__) ; 
 int /*<<< orphan*/  CHREC_RIGHT (scalar_t__) ; 
 int /*<<< orphan*/  CHREC_VARIABLE (scalar_t__) ; 
#define  MINUS_EXPR 130 
#define  MULT_EXPR 129 
#define  PLUS_EXPR 128 
 scalar_t__ POLYNOMIAL_CHREC ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ build_polynomial_chrec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ chrec_dont_know ; 
 int /*<<< orphan*/  chrec_fold_minus (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  chrec_fold_multiply (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  chrec_fold_plus (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ chrec_type (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  is_not_constant_evolution (scalar_t__) ; 

__attribute__((used)) static inline tree 
chrec_fold_poly_cst (enum tree_code code, 
		     tree type, 
		     tree poly, 
		     tree cst)
{
  gcc_assert (poly);
  gcc_assert (cst);
  gcc_assert (TREE_CODE (poly) == POLYNOMIAL_CHREC);
  gcc_assert (!is_not_constant_evolution (cst));
  gcc_assert (type == chrec_type (poly));

  switch (code)
    {
    case PLUS_EXPR:
      return build_polynomial_chrec 
	(CHREC_VARIABLE (poly), 
	 chrec_fold_plus (type, CHREC_LEFT (poly), cst),
	 CHREC_RIGHT (poly));
      
    case MINUS_EXPR:
      return build_polynomial_chrec 
	(CHREC_VARIABLE (poly), 
	 chrec_fold_minus (type, CHREC_LEFT (poly), cst),
	 CHREC_RIGHT (poly));
      
    case MULT_EXPR:
      return build_polynomial_chrec 
	(CHREC_VARIABLE (poly), 
	 chrec_fold_multiply (type, CHREC_LEFT (poly), cst),
	 chrec_fold_multiply (type, CHREC_RIGHT (poly), cst));
      
    default:
      return chrec_dont_know;
    }
}