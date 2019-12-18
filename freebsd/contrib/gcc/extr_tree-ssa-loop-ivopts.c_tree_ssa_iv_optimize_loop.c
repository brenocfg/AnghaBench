#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct loop {int num; } ;
struct ivopts_data {struct loop* current_loop; } ;
struct iv_ca {int dummy; } ;
typedef  TYPE_2__* edge ;
struct TYPE_7__ {int index; } ;
struct TYPE_6__ {TYPE_4__* src; TYPE_1__* dest; } ;
struct TYPE_5__ {int index; } ;

/* Variables and functions */
 scalar_t__ MAX_CONSIDERED_USES ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 int /*<<< orphan*/  create_new_ivs (struct ivopts_data*,struct iv_ca*) ; 
 int /*<<< orphan*/  determine_iv_costs (struct ivopts_data*) ; 
 int /*<<< orphan*/  determine_set_costs (struct ivopts_data*) ; 
 int /*<<< orphan*/  determine_use_iv_costs (struct ivopts_data*) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  find_induction_variables (struct ivopts_data*) ; 
 int /*<<< orphan*/  find_interesting_uses (struct ivopts_data*) ; 
 int /*<<< orphan*/  find_iv_candidates (struct ivopts_data*) ; 
 struct iv_ca* find_optimal_iv_set (struct ivopts_data*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  free_loop_data (struct ivopts_data*) ; 
 int /*<<< orphan*/  iv_ca_free (struct iv_ca**) ; 
 int /*<<< orphan*/  last_stmt (TYPE_4__*) ; 
 scalar_t__ n_iv_uses (struct ivopts_data*) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_unused_ivs (struct ivopts_data*) ; 
 int /*<<< orphan*/  rewrite_uses (struct ivopts_data*) ; 
 int /*<<< orphan*/  scev_reset () ; 
 TYPE_2__* single_dom_exit (struct loop*) ; 

__attribute__((used)) static bool
tree_ssa_iv_optimize_loop (struct ivopts_data *data, struct loop *loop)
{
  bool changed = false;
  struct iv_ca *iv_ca;
  edge exit;

  data->current_loop = loop;

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "Processing loop %d\n", loop->num);
      
      exit = single_dom_exit (loop);
      if (exit)
	{
	  fprintf (dump_file, "  single exit %d -> %d, exit condition ",
		   exit->src->index, exit->dest->index);
	  print_generic_expr (dump_file, last_stmt (exit->src), TDF_SLIM);
	  fprintf (dump_file, "\n");
	}

      fprintf (dump_file, "\n");
    }

  /* For each ssa name determines whether it behaves as an induction variable
     in some loop.  */
  if (!find_induction_variables (data))
    goto finish;

  /* Finds interesting uses (item 1).  */
  find_interesting_uses (data);
  if (n_iv_uses (data) > MAX_CONSIDERED_USES)
    goto finish;

  /* Finds candidates for the induction variables (item 2).  */
  find_iv_candidates (data);

  /* Calculates the costs (item 3, part 1).  */
  determine_use_iv_costs (data);
  determine_iv_costs (data);
  determine_set_costs (data);

  /* Find the optimal set of induction variables (item 3, part 2).  */
  iv_ca = find_optimal_iv_set (data);
  if (!iv_ca)
    goto finish;
  changed = true;

  /* Create the new induction variables (item 4, part 1).  */
  create_new_ivs (data, iv_ca);
  iv_ca_free (&iv_ca);
  
  /* Rewrite the uses (item 4, part 2).  */
  rewrite_uses (data);

  /* Remove the ivs that are unused after rewriting.  */
  remove_unused_ivs (data);

  /* We have changed the structure of induction variables; it might happen
     that definitions in the scev database refer to some of them that were
     eliminated.  */
  scev_reset ();

finish:
  free_loop_data (data);

  return changed;
}