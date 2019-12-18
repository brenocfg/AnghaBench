#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_2__ {int /*<<< orphan*/  num_miv_unimplemented; int /*<<< orphan*/  num_miv_dependent; int /*<<< orphan*/  num_miv_independent; int /*<<< orphan*/  num_miv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHREC_VARIABLE (scalar_t__) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  analyze_subscript_affine_affine (scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  chrec_contains_symbols (scalar_t__) ; 
 scalar_t__ chrec_convert (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ chrec_dont_know ; 
 scalar_t__ chrec_fold_minus (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ chrec_known ; 
 scalar_t__ chrec_steps_divide_constant_p (scalar_t__,scalar_t__,int*) ; 
 TYPE_1__ dependence_stats ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 scalar_t__ eq_evolutions_p (scalar_t__,scalar_t__) ; 
 scalar_t__ evolution_function_is_affine_multivariate_p (scalar_t__) ; 
 scalar_t__ evolution_function_is_constant_p (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 scalar_t__ get_number_of_iters_for_loop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_type_node ; 
 scalar_t__ integer_zero_node ; 

__attribute__((used)) static void
analyze_miv_subscript (tree chrec_a, 
		       tree chrec_b, 
		       tree *overlaps_a, 
		       tree *overlaps_b, 
		       tree *last_conflicts)
{
  /* FIXME:  This is a MIV subscript, not yet handled.
     Example: (A[{1, +, 1}_1] vs. A[{1, +, 1}_2]) that comes from 
     (A[i] vs. A[j]).  
     
     In the SIV test we had to solve a Diophantine equation with two
     variables.  In the MIV case we have to solve a Diophantine
     equation with 2*n variables (if the subscript uses n IVs).
  */
  bool divide_p = true;
  tree difference;
  dependence_stats.num_miv++;
  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "(analyze_miv_subscript \n");

  chrec_a = chrec_convert (integer_type_node, chrec_a, NULL_TREE);
  chrec_b = chrec_convert (integer_type_node, chrec_b, NULL_TREE);
  difference = chrec_fold_minus (integer_type_node, chrec_a, chrec_b);
  
  if (eq_evolutions_p (chrec_a, chrec_b))
    {
      /* Access functions are the same: all the elements are accessed
	 in the same order.  */
      *overlaps_a = integer_zero_node;
      *overlaps_b = integer_zero_node;
      *last_conflicts = get_number_of_iters_for_loop (CHREC_VARIABLE (chrec_a));
      dependence_stats.num_miv_dependent++;
    }
  
  else if (evolution_function_is_constant_p (difference)
	   /* For the moment, the following is verified:
	      evolution_function_is_affine_multivariate_p (chrec_a) */
	   && chrec_steps_divide_constant_p (chrec_a, difference, &divide_p)
	   && !divide_p)
    {
      /* testsuite/.../ssa-chrec-33.c
	 {{21, +, 2}_1, +, -2}_2  vs.  {{20, +, 2}_1, +, -2}_2 
	 
	 The difference is 1, and the evolution steps are equal to 2,
	 consequently there are no overlapping elements.  */
      *overlaps_a = chrec_known;
      *overlaps_b = chrec_known;
      *last_conflicts = integer_zero_node;
      dependence_stats.num_miv_independent++;
    }
  
  else if (evolution_function_is_affine_multivariate_p (chrec_a)
	   && !chrec_contains_symbols (chrec_a)
	   && evolution_function_is_affine_multivariate_p (chrec_b)
	   && !chrec_contains_symbols (chrec_b))
    {
      /* testsuite/.../ssa-chrec-35.c
	 {0, +, 1}_2  vs.  {0, +, 1}_3
	 the overlapping elements are respectively located at iterations:
	 {0, +, 1}_x and {0, +, 1}_x, 
	 in other words, we have the equality: 
	 {0, +, 1}_2 ({0, +, 1}_x) = {0, +, 1}_3 ({0, +, 1}_x)
	 
	 Other examples: 
	 {{0, +, 1}_1, +, 2}_2 ({0, +, 1}_x, {0, +, 1}_y) = 
	 {0, +, 1}_1 ({{0, +, 1}_x, +, 2}_y)

	 {{0, +, 2}_1, +, 3}_2 ({0, +, 1}_y, {0, +, 1}_x) = 
	 {{0, +, 3}_1, +, 2}_2 ({0, +, 1}_x, {0, +, 1}_y)
      */
      analyze_subscript_affine_affine (chrec_a, chrec_b, 
				       overlaps_a, overlaps_b, last_conflicts);

      if (*overlaps_a == chrec_dont_know
	  || *overlaps_b == chrec_dont_know)
	dependence_stats.num_miv_unimplemented++;
      else if (*overlaps_a == chrec_known
	       || *overlaps_b == chrec_known)
	dependence_stats.num_miv_independent++;
      else
	dependence_stats.num_miv_dependent++;
    }
  
  else
    {
      /* When the analysis is too difficult, answer "don't know".  */
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "analyze_miv_subscript test failed: unimplemented.\n");

      *overlaps_a = chrec_dont_know;
      *overlaps_b = chrec_dont_know;
      *last_conflicts = chrec_dont_know;
      dependence_stats.num_miv_unimplemented++;
    }
  
  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, ")\n");
}