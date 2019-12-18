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
struct iv_ca_delta {int /*<<< orphan*/  use; struct cost_pair* new_cp; struct cost_pair* old_cp; struct iv_ca_delta* next_change; } ;
struct iv_ca {int dummy; } ;
struct cost_pair {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (int) ; 
 struct cost_pair* iv_ca_cand_for_use (struct iv_ca*,int /*<<< orphan*/ ) ; 
 struct iv_ca_delta* iv_ca_delta_reverse (struct iv_ca_delta*) ; 
 int /*<<< orphan*/  iv_ca_set_cp (struct ivopts_data*,struct iv_ca*,int /*<<< orphan*/ ,struct cost_pair*) ; 

__attribute__((used)) static void
iv_ca_delta_commit (struct ivopts_data *data, struct iv_ca *ivs,
		    struct iv_ca_delta *delta, bool forward)
{
  struct cost_pair *from, *to;
  struct iv_ca_delta *act;

  if (!forward)
    delta = iv_ca_delta_reverse (delta);

  for (act = delta; act; act = act->next_change)
    {
      from = act->old_cp;
      to = act->new_cp;
      gcc_assert (iv_ca_cand_for_use (ivs, act->use) == from);
      iv_ca_set_cp (data, ivs, act->use, to);
    }

  if (!forward)
    iv_ca_delta_reverse (delta);
}