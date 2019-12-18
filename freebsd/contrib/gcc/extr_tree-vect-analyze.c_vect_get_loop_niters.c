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
struct loop {int dummy; } ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  REPORT_DETAILS ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 scalar_t__ chrec_dont_know ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_loop_exit_condition (struct loop*) ; 
 scalar_t__ number_of_iterations_in_loop (struct loop*) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vect_dump ; 
 scalar_t__ vect_print_dump_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
vect_get_loop_niters (struct loop *loop, tree *number_of_iterations)
{
  tree niters;

  if (vect_print_dump_info (REPORT_DETAILS))
    fprintf (vect_dump, "=== get_loop_niters ===");

  niters = number_of_iterations_in_loop (loop);

  if (niters != NULL_TREE
      && niters != chrec_dont_know)
    {
      *number_of_iterations = niters;

      if (vect_print_dump_info (REPORT_DETAILS))
	{
	  fprintf (vect_dump, "==> get_loop_niters:" );
	  print_generic_expr (vect_dump, *number_of_iterations, TDF_SLIM);
	}
    }

  return get_loop_exit_condition (loop);
}