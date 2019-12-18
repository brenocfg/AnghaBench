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
struct cost_pair {scalar_t__ cost; TYPE_1__* cand; } ;
struct TYPE_2__ {scalar_t__ cost; } ;

/* Variables and functions */

__attribute__((used)) static bool
cheaper_cost_pair (struct cost_pair *a, struct cost_pair *b)
{
  if (!a)
    return false;

  if (!b)
    return true;

  if (a->cost < b->cost)
    return true;

  if (a->cost > b->cost)
    return false;

  /* In case the costs are the same, prefer the cheaper candidate.  */
  if (a->cand->cost < b->cand->cost)
    return true;

  return false;
}