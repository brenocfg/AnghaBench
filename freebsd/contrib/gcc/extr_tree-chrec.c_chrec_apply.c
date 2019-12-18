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
 int /*<<< orphan*/  CHREC_LEFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHREC_RIGHT (int /*<<< orphan*/ ) ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ POLYNOMIAL_CHREC ; 
 scalar_t__ SCALAR_FLOAT_TYPE_P (int /*<<< orphan*/ ) ; 
 int TDF_DETAILS ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ automatically_generated_chrec_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_real_from_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ chrec_contains_symbols_defined_in_loop (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  chrec_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_dont_know ; 
 int /*<<< orphan*/  chrec_evaluate (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_fold_multiply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_fold_plus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_type (int /*<<< orphan*/ ) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 scalar_t__ evolution_function_is_affine_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  integer_zerop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tree_int_cst_sgn (int /*<<< orphan*/ ) ; 

tree 
chrec_apply (unsigned var,
	     tree chrec, 
	     tree x)
{
  tree type = chrec_type (chrec);
  tree res = chrec_dont_know;

  if (automatically_generated_chrec_p (chrec)
      || automatically_generated_chrec_p (x)

      /* When the symbols are defined in an outer loop, it is possible
	 to symbolically compute the apply, since the symbols are
	 constants with respect to the varying loop.  */
      || chrec_contains_symbols_defined_in_loop (chrec, var))
    return chrec_dont_know;
 
  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "(chrec_apply \n");

  if (TREE_CODE (x) == INTEGER_CST && SCALAR_FLOAT_TYPE_P (type))
    x = build_real_from_int_cst (type, x);

  if (evolution_function_is_affine_p (chrec))
    {
      /* "{a, +, b} (x)"  ->  "a + b*x".  */
      x = chrec_convert (type, x, NULL_TREE);
      res = chrec_fold_multiply (type, CHREC_RIGHT (chrec), x);
      if (!integer_zerop (CHREC_LEFT (chrec)))
	res = chrec_fold_plus (type, CHREC_LEFT (chrec), res);
    }
  
  else if (TREE_CODE (chrec) != POLYNOMIAL_CHREC)
    res = chrec;
  
  else if (TREE_CODE (x) == INTEGER_CST
	   && tree_int_cst_sgn (x) == 1)
    /* testsuite/.../ssa-chrec-38.c.  */
    res = chrec_evaluate (var, chrec, x, 0);
  else
    res = chrec_dont_know;
  
  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "  (varying_loop = %d\n", var);
      fprintf (dump_file, ")\n  (chrec = ");
      print_generic_expr (dump_file, chrec, 0);
      fprintf (dump_file, ")\n  (x = ");
      print_generic_expr (dump_file, x, 0);
      fprintf (dump_file, ")\n  (res = ");
      print_generic_expr (dump_file, res, 0);
      fprintf (dump_file, "))\n");
    }
  
  return res;
}