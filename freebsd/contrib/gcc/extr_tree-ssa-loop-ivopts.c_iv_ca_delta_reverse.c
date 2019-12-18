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
struct iv_ca_delta {struct cost_pair* new_cp; struct cost_pair* old_cp; struct iv_ca_delta* next_change; } ;
struct cost_pair {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct iv_ca_delta *
iv_ca_delta_reverse (struct iv_ca_delta *delta)
{
  struct iv_ca_delta *act, *next, *prev = NULL;
  struct cost_pair *tmp;

  for (act = delta; act; act = next)
    {
      next = act->next_change;
      act->next_change = prev;
      prev = act;

      tmp = act->old_cp;
      act->old_cp = act->new_cp;
      act->new_cp = tmp;
    }

  return prev;
}