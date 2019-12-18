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
struct loop {int num; } ;

/* Variables and functions */
 scalar_t__ SSA_NAME ; 
 int TDF_DETAILS ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ analyze_scalar_evolution_1 (struct loop*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ chrec_dont_know ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  get_scalar_evolution (scalar_t__) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

tree 
analyze_scalar_evolution (struct loop *loop, tree var)
{
  tree res;

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "(analyze_scalar_evolution \n");
      fprintf (dump_file, "  (loop_nb = %d)\n", loop->num);
      fprintf (dump_file, "  (scalar = ");
      print_generic_expr (dump_file, var, 0);
      fprintf (dump_file, ")\n");
    }

  res = analyze_scalar_evolution_1 (loop, var, get_scalar_evolution (var));

  if (TREE_CODE (var) == SSA_NAME && res == chrec_dont_know)
    res = var;

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, ")\n");

  return res;
}