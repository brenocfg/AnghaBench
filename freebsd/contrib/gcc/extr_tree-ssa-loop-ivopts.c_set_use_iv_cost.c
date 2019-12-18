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
typedef  void* tree ;
struct ivopts_data {scalar_t__ consider_all_candidates; } ;
struct iv_use {int n_map_members; TYPE_1__* cost_map; } ;
struct iv_cand {size_t id; } ;
typedef  void* bitmap ;
struct TYPE_2__ {unsigned int cost; void* value; void* depends_on; struct iv_cand* cand; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_FREE (void*) ; 
 unsigned int INFTY ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static void
set_use_iv_cost (struct ivopts_data *data,
		 struct iv_use *use, struct iv_cand *cand, unsigned cost,
		 bitmap depends_on, tree value)
{
  unsigned i, s;

  if (cost == INFTY)
    {
      BITMAP_FREE (depends_on);
      return;
    }

  if (data->consider_all_candidates)
    {
      use->cost_map[cand->id].cand = cand;
      use->cost_map[cand->id].cost = cost;
      use->cost_map[cand->id].depends_on = depends_on;
      use->cost_map[cand->id].value = value;
      return;
    }

  /* n_map_members is a power of two, so this computes modulo.  */
  s = cand->id & (use->n_map_members - 1);
  for (i = s; i < use->n_map_members; i++)
    if (!use->cost_map[i].cand)
      goto found;
  for (i = 0; i < s; i++)
    if (!use->cost_map[i].cand)
      goto found;

  gcc_unreachable ();

found:
  use->cost_map[i].cand = cand;
  use->cost_map[i].cost = cost;
  use->cost_map[i].depends_on = depends_on;
  use->cost_map[i].value = value;
}