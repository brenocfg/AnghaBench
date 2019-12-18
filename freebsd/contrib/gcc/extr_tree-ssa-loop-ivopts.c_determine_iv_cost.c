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
typedef  int /*<<< orphan*/  tree ;
struct ivopts_data {int /*<<< orphan*/  current_loop; } ;
struct iv_cand {unsigned int cost; scalar_t__ pos; int /*<<< orphan*/  var_before; TYPE_1__* iv; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 unsigned int AVG_LOOP_NITER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_ARTIFICIAL (int /*<<< orphan*/ ) ; 
 scalar_t__ IP_END ; 
 scalar_t__ IP_ORIGINAL ; 
 int /*<<< orphan*/  SSA_NAME_VAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 unsigned int add_cost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_loop ; 
 scalar_t__ empty_block_p (int /*<<< orphan*/ ) ; 
 unsigned int force_var_cost (struct ivopts_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_end_pos (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
determine_iv_cost (struct ivopts_data *data, struct iv_cand *cand)
{
  unsigned cost_base, cost_step;
  tree base;

  if (!cand->iv)
    {
      cand->cost = 0;
      return;
    }

  /* There are two costs associated with the candidate -- its increment
     and its initialization.  The second is almost negligible for any loop
     that rolls enough, so we take it just very little into account.  */

  base = cand->iv->base;
  cost_base = force_var_cost (data, base, NULL);
  cost_step = add_cost (TYPE_MODE (TREE_TYPE (base)));

  cand->cost = cost_step + cost_base / AVG_LOOP_NITER (current_loop);

  /* Prefer the original iv unless we may gain something by replacing it;
     this is not really relevant for artificial ivs created by other
     passes.  */
  if (cand->pos == IP_ORIGINAL
      && !DECL_ARTIFICIAL (SSA_NAME_VAR (cand->var_before)))
    cand->cost--;
  
  /* Prefer not to insert statements into latch unless there are some
     already (so that we do not create unnecessary jumps).  */
  if (cand->pos == IP_END
      && empty_block_p (ip_end_pos (data->current_loop)))
    cand->cost++;
}