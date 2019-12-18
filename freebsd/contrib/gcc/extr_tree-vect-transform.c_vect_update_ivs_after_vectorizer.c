#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct loop {int /*<<< orphan*/  num; int /*<<< orphan*/  header; TYPE_1__* single_exit; } ;
typedef  int /*<<< orphan*/  loop_vec_info ;
typedef  TYPE_2__* edge ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_5__ {int /*<<< orphan*/  dest_idx; int /*<<< orphan*/  dest; } ;
struct TYPE_4__ {int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSI_SAME_STMT ; 
 struct loop* LOOP_VINFO_LOOP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MULT_EXPR ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  PHI_RESULT (scalar_t__) ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  REPORT_DETAILS ; 
 int /*<<< orphan*/  SET_PHI_ARG_DEF (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SSA_NAME_VAR (int /*<<< orphan*/ ) ; 
 scalar_t__ STMT_VINFO_DEF_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  add_referenced_var (scalar_t__) ; 
 scalar_t__ analyze_scalar_evolution (struct loop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_insert_before (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_last (int /*<<< orphan*/ ) ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ create_tmp_var (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evolution_part_in_loop_num (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ force_gimple_operand (scalar_t__,scalar_t__*,int,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  initial_condition_in_loop_num (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gimple_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ phi_nodes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int single_pred_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_is_chrec (scalar_t__) ; 
 scalar_t__ unshare_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vect_dump ; 
 scalar_t__ vect_print_dump_info (int /*<<< orphan*/ ) ; 
 scalar_t__ vect_reduction_def ; 
 int /*<<< orphan*/  vinfo_for_stmt (scalar_t__) ; 

__attribute__((used)) static void
vect_update_ivs_after_vectorizer (loop_vec_info loop_vinfo, tree niters, 
				  edge update_e)
{
  struct loop *loop = LOOP_VINFO_LOOP (loop_vinfo);
  basic_block exit_bb = loop->single_exit->dest;
  tree phi, phi1;
  basic_block update_bb = update_e->dest;

  /* gcc_assert (vect_can_advance_ivs_p (loop_vinfo)); */

  /* Make sure there exists a single-predecessor exit bb:  */
  gcc_assert (single_pred_p (exit_bb));

  for (phi = phi_nodes (loop->header), phi1 = phi_nodes (update_bb); 
       phi && phi1; 
       phi = PHI_CHAIN (phi), phi1 = PHI_CHAIN (phi1))
    {
      tree access_fn = NULL;
      tree evolution_part;
      tree init_expr;
      tree step_expr;
      tree var, stmt, ni, ni_name;
      block_stmt_iterator last_bsi;

      if (vect_print_dump_info (REPORT_DETAILS))
        {
          fprintf (vect_dump, "vect_update_ivs_after_vectorizer: phi: ");
          print_generic_expr (vect_dump, phi, TDF_SLIM);
        }

      /* Skip virtual phi's.  */
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

      access_fn = analyze_scalar_evolution (loop, PHI_RESULT (phi)); 
      gcc_assert (access_fn);
      evolution_part =
	 unshare_expr (evolution_part_in_loop_num (access_fn, loop->num));
      gcc_assert (evolution_part != NULL_TREE);
      
      /* FORNOW: We do not support IVs whose evolution function is a polynomial
         of degree >= 2 or exponential.  */
      gcc_assert (!tree_is_chrec (evolution_part));

      step_expr = evolution_part;
      init_expr = unshare_expr (initial_condition_in_loop_num (access_fn, 
							       loop->num));

      ni = build2 (PLUS_EXPR, TREE_TYPE (init_expr),
		  build2 (MULT_EXPR, TREE_TYPE (niters),
		       niters, step_expr), init_expr);

      var = create_tmp_var (TREE_TYPE (init_expr), "tmp");
      add_referenced_var (var);

      ni_name = force_gimple_operand (ni, &stmt, false, var);
      
      /* Insert stmt into exit_bb.  */
      last_bsi = bsi_last (exit_bb);
      if (stmt)
        bsi_insert_before (&last_bsi, stmt, BSI_SAME_STMT);   

      /* Fix phi expressions in the successor bb.  */
      SET_PHI_ARG_DEF (phi1, update_e->dest_idx, ni_name);
    }
}