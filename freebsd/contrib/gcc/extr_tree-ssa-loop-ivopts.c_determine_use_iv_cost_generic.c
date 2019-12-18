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
struct iv_use {scalar_t__ stmt; } ;
struct iv_cand {scalar_t__ pos; scalar_t__ incremented_at; } ;
typedef  int /*<<< orphan*/ * bitmap ;

/* Variables and functions */
 unsigned int INFTY ; 
 scalar_t__ IP_ORIGINAL ; 
 int /*<<< orphan*/  NULL_TREE ; 
 unsigned int get_computation_cost (struct ivopts_data*,struct iv_use*,struct iv_cand*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  set_use_iv_cost (struct ivopts_data*,struct iv_use*,struct iv_cand*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
determine_use_iv_cost_generic (struct ivopts_data *data,
			       struct iv_use *use, struct iv_cand *cand)
{
  bitmap depends_on;
  unsigned cost;

  /* The simple case first -- if we need to express value of the preserved
     original biv, the cost is 0.  This also prevents us from counting the
     cost of increment twice -- once at this use and once in the cost of
     the candidate.  */
  if (cand->pos == IP_ORIGINAL
      && cand->incremented_at == use->stmt)
    {
      set_use_iv_cost (data, use, cand, 0, NULL, NULL_TREE);
      return true;
    }

  cost = get_computation_cost (data, use, cand, false, &depends_on);
  set_use_iv_cost (data, use, cand, cost, depends_on, NULL_TREE);

  return cost != INFTY;
}