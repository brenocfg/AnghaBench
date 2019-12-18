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
struct iv_use {int dummy; } ;
struct iv_cand {int dummy; } ;
struct iv_ca_delta {int dummy; } ;
struct iv_ca {unsigned int upto; } ;
struct cost_pair {struct iv_cand* cand; } ;

/* Variables and functions */
 int /*<<< orphan*/  cheaper_cost_pair (struct cost_pair*,struct cost_pair*) ; 
 struct cost_pair* get_use_iv_cost (struct ivopts_data*,struct iv_use*,struct iv_cand*) ; 
 struct cost_pair* iv_ca_cand_for_use (struct iv_ca*,struct iv_use*) ; 
 unsigned int iv_ca_cost (struct iv_ca*) ; 
 struct iv_ca_delta* iv_ca_delta_add (struct iv_use*,struct cost_pair*,struct cost_pair*,struct iv_ca_delta*) ; 
 int /*<<< orphan*/  iv_ca_delta_commit (struct ivopts_data*,struct iv_ca*,struct iv_ca_delta*,int) ; 
 int /*<<< orphan*/  iv_ca_has_deps (struct iv_ca*,struct cost_pair*) ; 
 unsigned int iv_ca_n_cands (struct iv_ca*) ; 
 struct iv_use* iv_use (struct ivopts_data*,unsigned int) ; 

__attribute__((used)) static unsigned
iv_ca_extend (struct ivopts_data *data, struct iv_ca *ivs,
	      struct iv_cand *cand, struct iv_ca_delta **delta,
	      unsigned *n_ivs)
{
  unsigned i, cost;
  struct iv_use *use;
  struct cost_pair *old_cp, *new_cp;

  *delta = NULL;
  for (i = 0; i < ivs->upto; i++)
    {
      use = iv_use (data, i);
      old_cp = iv_ca_cand_for_use (ivs, use);

      if (old_cp
	  && old_cp->cand == cand)
	continue;

      new_cp = get_use_iv_cost (data, use, cand);
      if (!new_cp)
	continue;

      if (!iv_ca_has_deps (ivs, new_cp))
	continue;
      
      if (!cheaper_cost_pair (new_cp, old_cp))
	continue;

      *delta = iv_ca_delta_add (use, old_cp, new_cp, *delta);
    }

  iv_ca_delta_commit (data, ivs, *delta, true);
  cost = iv_ca_cost (ivs);
  if (n_ivs)
    *n_ivs = iv_ca_n_cands (ivs);
  iv_ca_delta_commit (data, ivs, *delta, false);

  return cost;
}