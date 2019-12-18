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
struct loop {int /*<<< orphan*/  num; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parray; } ;

/* Variables and functions */
 size_t CHREC_VARIABLE (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ POLYNOMIAL_CHREC ; 
 int TDF_DETAILS ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  analyze_scalar_evolution (struct loop*,scalar_t__) ; 
 TYPE_1__* current_loops ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 scalar_t__ evolution_part_in_loop_num (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 scalar_t__ initial_condition_in_loop_num (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ instantiate_parameters (struct loop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gimple_min_invariant (scalar_t__) ; 
 struct loop* loop_containing_stmt (scalar_t__) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ scev_probably_wraps_p (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  valid_value_p (scalar_t__) ; 

__attribute__((used)) static bool
vrp_var_may_overflow (tree var, tree stmt)
{
  struct loop *l;
  tree chrec, init, step;

  if (current_loops == NULL)
    return true;

  l = loop_containing_stmt (stmt);
  if (l == NULL)
    return true;

  chrec = instantiate_parameters (l, analyze_scalar_evolution (l, var));
  if (TREE_CODE (chrec) != POLYNOMIAL_CHREC)
    return true;

  init = initial_condition_in_loop_num (chrec, l->num);
  step = evolution_part_in_loop_num (chrec, l->num);

  if (step == NULL_TREE
      || !is_gimple_min_invariant (step)
      || !valid_value_p (init))
    return true;

  /* If we get here, we know something useful about VAR based on the
     loop information.  If it wraps, it may overflow.  */

  if (scev_probably_wraps_p (init, step, stmt,
			     current_loops->parray[CHREC_VARIABLE (chrec)],
			     true))
    return true;

  if (dump_file && (dump_flags & TDF_DETAILS) != 0)
    {
      print_generic_expr (dump_file, var, 0);
      fprintf (dump_file, ": loop information indicates does not overflow\n");
    }

  return false;
}