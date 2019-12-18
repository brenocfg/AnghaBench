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
struct cgraph_edge {int count; } ;
struct TYPE_2__ {int sum_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOT_BB_COUNT_FRACTION ; 
 int PARAM_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_branch_probabilities ; 
 TYPE_1__* profile_info ; 

__attribute__((used)) static bool
cgraph_maybe_hot_edge_p (struct cgraph_edge *edge)
{
  if (profile_info && flag_branch_probabilities
      && (edge->count
	  <= profile_info->sum_max / PARAM_VALUE (HOT_BB_COUNT_FRACTION)))
    return false;
  return true;
}