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
typedef  int /*<<< orphan*/ * tree ;
struct omp_region {scalar_t__ type; int is_combined_parallel; int /*<<< orphan*/  ws_args; TYPE_1__* inner; int /*<<< orphan*/ * exit; int /*<<< orphan*/ * entry; } ;
typedef  int /*<<< orphan*/ * basic_block ;
struct TYPE_2__ {scalar_t__ type; int is_combined_parallel; int /*<<< orphan*/ * exit; int /*<<< orphan*/ * entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMP_CLAUSE_ORDERED ; 
 int /*<<< orphan*/  OMP_CLAUSE_SCHEDULE ; 
 scalar_t__ OMP_CLAUSE_SCHEDULE_KIND (int /*<<< orphan*/ *) ; 
 scalar_t__ OMP_CLAUSE_SCHEDULE_STATIC ; 
 scalar_t__ OMP_FOR ; 
 int /*<<< orphan*/ * OMP_FOR_CLAUSES (int /*<<< orphan*/ *) ; 
 scalar_t__ OMP_PARALLEL ; 
 scalar_t__ OMP_PARALLEL_COMBINED (int /*<<< orphan*/ *) ; 
 scalar_t__ OMP_SECTIONS ; 
 int /*<<< orphan*/ * find_omp_clause (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ws_args_for (int /*<<< orphan*/ *) ; 
 scalar_t__ last_and_only_stmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * last_stmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * single_succ (int /*<<< orphan*/ *) ; 
 scalar_t__ workshare_safe_to_combine_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
determine_parallel_type (struct omp_region *region)
{
  basic_block par_entry_bb, par_exit_bb;
  basic_block ws_entry_bb, ws_exit_bb;

  if (region == NULL || region->inner == NULL
      || region->exit == NULL || region->inner->exit == NULL)
    return;

  /* We only support parallel+for and parallel+sections.  */
  if (region->type != OMP_PARALLEL
      || (region->inner->type != OMP_FOR
	  && region->inner->type != OMP_SECTIONS))
    return;

  /* Check for perfect nesting PAR_ENTRY_BB -> WS_ENTRY_BB and
     WS_EXIT_BB -> PAR_EXIT_BB.  */
  par_entry_bb = region->entry;
  par_exit_bb = region->exit;
  ws_entry_bb = region->inner->entry;
  ws_exit_bb = region->inner->exit;

  if (single_succ (par_entry_bb) == ws_entry_bb
      && single_succ (ws_exit_bb) == par_exit_bb
      && workshare_safe_to_combine_p (par_entry_bb, ws_entry_bb)
      && (OMP_PARALLEL_COMBINED (last_stmt (par_entry_bb))
	  || (last_and_only_stmt (ws_entry_bb)
	      && last_and_only_stmt (par_exit_bb))))
    {
      tree ws_stmt = last_stmt (ws_entry_bb);

      if (region->inner->type == OMP_FOR)
	{
	  /* If this is a combined parallel loop, we need to determine
	     whether or not to use the combined library calls.  There
	     are two cases where we do not apply the transformation:
	     static loops and any kind of ordered loop.  In the first
	     case, we already open code the loop so there is no need
	     to do anything else.  In the latter case, the combined
	     parallel loop call would still need extra synchronization
	     to implement ordered semantics, so there would not be any
	     gain in using the combined call.  */
	  tree clauses = OMP_FOR_CLAUSES (ws_stmt);
	  tree c = find_omp_clause (clauses, OMP_CLAUSE_SCHEDULE);
	  if (c == NULL
	      || OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_STATIC
	      || find_omp_clause (clauses, OMP_CLAUSE_ORDERED))
	    {
	      region->is_combined_parallel = false;
	      region->inner->is_combined_parallel = false;
	      return;
	    }
	}

      region->is_combined_parallel = true;
      region->inner->is_combined_parallel = true;
      region->ws_args = get_ws_args_for (ws_stmt);
    }
}