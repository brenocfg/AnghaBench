#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct loop {int /*<<< orphan*/  header; } ;
struct ivopts_data {struct loop* current_loop; } ;
struct iv {int biv_p; } ;
typedef  TYPE_1__* basic_block ;
struct TYPE_3__ {int flags; struct loop* loop_father; } ;

/* Variables and functions */
 int BB_IRREDUCIBLE_LOOP ; 
 scalar_t__ PHI_ARG_DEF_FROM_EDGE (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 scalar_t__ PHI_RESULT (scalar_t__) ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (scalar_t__) ; 
 TYPE_1__* bb_for_stmt (int /*<<< orphan*/ ) ; 
 struct iv* get_iv (struct ivopts_data*,scalar_t__) ; 
 int /*<<< orphan*/  loop_latch_edge (struct loop*) ; 
 scalar_t__ phi_nodes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mark_bivs (struct ivopts_data *data)
{
  tree phi, var;
  struct iv *iv, *incr_iv;
  struct loop *loop = data->current_loop;
  basic_block incr_bb;

  for (phi = phi_nodes (loop->header); phi; phi = PHI_CHAIN (phi))
    {
      iv = get_iv (data, PHI_RESULT (phi));
      if (!iv)
	continue;

      var = PHI_ARG_DEF_FROM_EDGE (phi, loop_latch_edge (loop));
      incr_iv = get_iv (data, var);
      if (!incr_iv)
	continue;

      /* If the increment is in the subloop, ignore it.  */
      incr_bb = bb_for_stmt (SSA_NAME_DEF_STMT (var));
      if (incr_bb->loop_father != data->current_loop
	  || (incr_bb->flags & BB_IRREDUCIBLE_LOOP))
	continue;

      iv->biv_p = true;
      incr_iv->biv_p = true;
    }
}