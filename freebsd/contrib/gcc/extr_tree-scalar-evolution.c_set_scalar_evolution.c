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
 scalar_t__ SSA_NAME ; 
 int TDF_DETAILS ; 
 int TDF_STATS ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/ * find_var_scev_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  nb_set_scev ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_scalar_evolution (tree scalar, tree chrec)
{
  tree *scalar_info;
 
  if (TREE_CODE (scalar) != SSA_NAME)
    return;

  scalar_info = find_var_scev_info (scalar);
  
  if (dump_file)
    {
      if (dump_flags & TDF_DETAILS)
	{
	  fprintf (dump_file, "(set_scalar_evolution \n");
	  fprintf (dump_file, "  (scalar = ");
	  print_generic_expr (dump_file, scalar, 0);
	  fprintf (dump_file, ")\n  (scalar_evolution = ");
	  print_generic_expr (dump_file, chrec, 0);
	  fprintf (dump_file, "))\n");
	}
      if (dump_flags & TDF_STATS)
	nb_set_scev++;
    }
  
  *scalar_info = chrec;
}