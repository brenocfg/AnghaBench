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
 int /*<<< orphan*/  CHREC_VARIABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_polynomial_chrec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ chrec_contains_symbols (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_fold_minus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_type (int /*<<< orphan*/ ) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  evolution_function_is_constant_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 

__attribute__((used)) static bool
can_use_analyze_subscript_affine_affine (tree *chrec_a, tree *chrec_b)
{
  tree diff, type, left_a, left_b, right_b;

  if (chrec_contains_symbols (CHREC_RIGHT (*chrec_a))
      || chrec_contains_symbols (CHREC_RIGHT (*chrec_b)))
    /* FIXME: For the moment not handled.  Might be refined later.  */
    return false;

  type = chrec_type (*chrec_a);
  left_a = CHREC_LEFT (*chrec_a);
  left_b = chrec_convert (type, CHREC_LEFT (*chrec_b), NULL_TREE);
  diff = chrec_fold_minus (type, left_a, left_b);

  if (!evolution_function_is_constant_p (diff))
    return false;

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "can_use_subscript_aff_aff_for_symbolic \n");

  *chrec_a = build_polynomial_chrec (CHREC_VARIABLE (*chrec_a), 
				     diff, CHREC_RIGHT (*chrec_a));
  right_b = chrec_convert (type, CHREC_RIGHT (*chrec_b), NULL_TREE);
  *chrec_b = build_polynomial_chrec (CHREC_VARIABLE (*chrec_b),
				     build_int_cst (type, 0),
				     right_b);
  return true;
}