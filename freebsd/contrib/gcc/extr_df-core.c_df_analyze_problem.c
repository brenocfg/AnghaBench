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
struct dataflow {TYPE_1__* problem; } ;
typedef  int /*<<< orphan*/  bitmap ;
struct TYPE_2__ {int /*<<< orphan*/  (* finalize_fun ) (struct dataflow*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* dataflow_fun ) (struct dataflow*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ;int /*<<< orphan*/  (* local_compute_fun ) (struct dataflow*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* alloc_fun ) (struct dataflow*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dataflow*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct dataflow*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct dataflow*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct dataflow*,int /*<<< orphan*/ ) ; 

void
df_analyze_problem (struct dataflow *dflow, 
		    bitmap blocks_to_consider, 
		    bitmap blocks_to_init,
		    bitmap blocks_to_scan,
		    int *postorder, int n_blocks, bool single_pass)
{
  /* (Re)Allocate the datastructures necessary to solve the problem.  */ 
  if (dflow->problem->alloc_fun)
    dflow->problem->alloc_fun (dflow, blocks_to_scan, blocks_to_init);

  /* Set up the problem and compute the local information.  This
     function is passed both the blocks_to_consider and the
     blocks_to_scan because the RD and RU problems require the entire
     function to be rescanned if they are going to be updated.  */
  if (dflow->problem->local_compute_fun)
    dflow->problem->local_compute_fun (dflow, blocks_to_consider, blocks_to_scan);

  /* Solve the equations.  */
  if (dflow->problem->dataflow_fun)
    dflow->problem->dataflow_fun (dflow, blocks_to_consider, blocks_to_init,
				  postorder, n_blocks, single_pass);

  /* Massage the solution.  */
  if (dflow->problem->finalize_fun)
    dflow->problem->finalize_fun (dflow, blocks_to_consider);
}