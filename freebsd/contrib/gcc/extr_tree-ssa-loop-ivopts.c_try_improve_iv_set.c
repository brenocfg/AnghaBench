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
struct ivopts_data {int dummy; } ;
struct iv_cand {int dummy; } ;
struct iv_ca_delta {int dummy; } ;
struct iv_ca {int dummy; } ;

/* Variables and functions */
 unsigned int ALWAYS_PRUNE_CAND_SET_BOUND ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ iv_ca_cand_used_p (struct iv_ca*,struct iv_cand*) ; 
 unsigned int iv_ca_cost (struct iv_ca*) ; 
 int /*<<< orphan*/  iv_ca_delta_commit (struct ivopts_data*,struct iv_ca*,struct iv_ca_delta*,int) ; 
 int /*<<< orphan*/  iv_ca_delta_free (struct iv_ca_delta**) ; 
 struct iv_ca_delta* iv_ca_delta_join (struct iv_ca_delta*,struct iv_ca_delta*) ; 
 unsigned int iv_ca_extend (struct ivopts_data*,struct iv_ca*,struct iv_cand*,struct iv_ca_delta**,unsigned int*) ; 
 unsigned int iv_ca_prune (struct ivopts_data*,struct iv_ca*,struct iv_cand*,struct iv_ca_delta**) ; 
 struct iv_cand* iv_cand (struct ivopts_data*,unsigned int) ; 
 unsigned int n_iv_cands (struct ivopts_data*) ; 

__attribute__((used)) static bool
try_improve_iv_set (struct ivopts_data *data, struct iv_ca *ivs)
{
  unsigned i, acost, best_cost = iv_ca_cost (ivs), n_ivs;
  struct iv_ca_delta *best_delta = NULL, *act_delta, *tmp_delta;
  struct iv_cand *cand;

  /* Try extending the set of induction variables by one.  */
  for (i = 0; i < n_iv_cands (data); i++)
    {
      cand = iv_cand (data, i);
      
      if (iv_ca_cand_used_p (ivs, cand))
	continue;

      acost = iv_ca_extend (data, ivs, cand, &act_delta, &n_ivs);
      if (!act_delta)
	continue;

      /* If we successfully added the candidate and the set is small enough,
	 try optimizing it by removing other candidates.  */
      if (n_ivs <= ALWAYS_PRUNE_CAND_SET_BOUND)
      	{
	  iv_ca_delta_commit (data, ivs, act_delta, true);
	  acost = iv_ca_prune (data, ivs, cand, &tmp_delta);
	  iv_ca_delta_commit (data, ivs, act_delta, false);
	  act_delta = iv_ca_delta_join (act_delta, tmp_delta);
	}

      if (acost < best_cost)
	{
	  best_cost = acost;
	  iv_ca_delta_free (&best_delta);
	  best_delta = act_delta;
	}
      else
	iv_ca_delta_free (&act_delta);
    }

  if (!best_delta)
    {
      /* Try removing the candidates from the set instead.  */
      best_cost = iv_ca_prune (data, ivs, NULL, &best_delta);

      /* Nothing more we can do.  */
      if (!best_delta)
	return false;
    }

  iv_ca_delta_commit (data, ivs, best_delta, true);
  gcc_assert (best_cost == iv_ca_cost (ivs));
  iv_ca_delta_free (&best_delta);
  return true;
}