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
struct ivopts_data {scalar_t__ consider_all_candidates; } ;
struct iv_use {int n_map_members; struct cost_pair* cost_map; } ;
struct iv_cand {int id; } ;
struct cost_pair {struct iv_cand* cand; } ;

/* Variables and functions */

__attribute__((used)) static struct cost_pair *
get_use_iv_cost (struct ivopts_data *data, struct iv_use *use,
		 struct iv_cand *cand)
{
  unsigned i, s;
  struct cost_pair *ret;

  if (!cand)
    return NULL;

  if (data->consider_all_candidates)
    {
      ret = use->cost_map + cand->id;
      if (!ret->cand)
	return NULL;

      return ret;
    }
      
  /* n_map_members is a power of two, so this computes modulo.  */
  s = cand->id & (use->n_map_members - 1);
  for (i = s; i < use->n_map_members; i++)
    if (use->cost_map[i].cand == cand)
      return use->cost_map + i;

  for (i = 0; i < s; i++)
    if (use->cost_map[i].cand == cand)
      return use->cost_map + i;

  return NULL;
}