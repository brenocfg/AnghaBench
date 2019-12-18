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
struct loop {int /*<<< orphan*/  num; int /*<<< orphan*/  header; } ;
typedef  int /*<<< orphan*/  loop_vec_info ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 struct loop* LOOP_VINFO_LOOP (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  PHI_RESULT (scalar_t__) ; 
 int /*<<< orphan*/  REPORT_DETAILS ; 
 int /*<<< orphan*/  SSA_NAME_VAR (int /*<<< orphan*/ ) ; 
 scalar_t__ STMT_VINFO_DEF_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 int /*<<< orphan*/  analyze_scalar_evolution (struct loop*,int /*<<< orphan*/ ) ; 
 scalar_t__ evolution_part_in_loop_num (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ instantiate_parameters (struct loop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gimple_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ phi_nodes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ tree_is_chrec (scalar_t__) ; 
 int /*<<< orphan*/  vect_dump ; 
 scalar_t__ vect_print_dump_info (int /*<<< orphan*/ ) ; 
 scalar_t__ vect_reduction_def ; 
 int /*<<< orphan*/  vinfo_for_stmt (scalar_t__) ; 

__attribute__((used)) static bool 
vect_can_advance_ivs_p (loop_vec_info loop_vinfo)
{
  struct loop *loop = LOOP_VINFO_LOOP (loop_vinfo);
  basic_block bb = loop->header;
  tree phi;

  /* Analyze phi functions of the loop header.  */

  if (vect_print_dump_info (REPORT_DETAILS))
    fprintf (vect_dump, "=== vect_can_advance_ivs_p ===");

  for (phi = phi_nodes (bb); phi; phi = PHI_CHAIN (phi))
    {
      tree access_fn = NULL;
      tree evolution_part;

      if (vect_print_dump_info (REPORT_DETAILS))
	{
          fprintf (vect_dump, "Analyze phi: ");
          print_generic_expr (vect_dump, phi, TDF_SLIM);
	}

      /* Skip virtual phi's. The data dependences that are associated with
         virtual defs/uses (i.e., memory accesses) are analyzed elsewhere.  */

      if (!is_gimple_reg (SSA_NAME_VAR (PHI_RESULT (phi))))
	{
	  if (vect_print_dump_info (REPORT_DETAILS))
	    fprintf (vect_dump, "virtual phi. skip.");
	  continue;
	}

      /* Skip reduction phis.  */

      if (STMT_VINFO_DEF_TYPE (vinfo_for_stmt (phi)) == vect_reduction_def)
        {
          if (vect_print_dump_info (REPORT_DETAILS))
            fprintf (vect_dump, "reduc phi. skip.");
          continue;
        }

      /* Analyze the evolution function.  */

      access_fn = instantiate_parameters
	(loop, analyze_scalar_evolution (loop, PHI_RESULT (phi)));

      if (!access_fn)
	{
	  if (vect_print_dump_info (REPORT_DETAILS))
	    fprintf (vect_dump, "No Access function.");
	  return false;
	}

      if (vect_print_dump_info (REPORT_DETAILS))
        {
	  fprintf (vect_dump, "Access function of PHI: ");
	  print_generic_expr (vect_dump, access_fn, TDF_SLIM);
        }

      evolution_part = evolution_part_in_loop_num (access_fn, loop->num);
      
      if (evolution_part == NULL_TREE)
        {
	  if (vect_print_dump_info (REPORT_DETAILS))
	    fprintf (vect_dump, "No evolution.");
	  return false;
        }
  
      /* FORNOW: We do not transform initial conditions of IVs 
	 which evolution functions are a polynomial of degree >= 2.  */

      if (tree_is_chrec (evolution_part))
	return false;  
    }

  return true;
}