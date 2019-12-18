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
struct z_candidate {int viable; struct z_candidate* next; } ;

/* Variables and functions */

__attribute__((used)) static struct z_candidate*
splice_viable (struct z_candidate *cands,
	       bool strict_p,
	       bool *any_viable_p)
{
  struct z_candidate *viable;
  struct z_candidate **last_viable;
  struct z_candidate **cand;

  viable = NULL;
  last_viable = &viable;
  *any_viable_p = false;

  cand = &cands;
  while (*cand)
    {
      struct z_candidate *c = *cand;
      if (strict_p ? c->viable == 1 : c->viable)
	{
	  *last_viable = c;
	  *cand = c->next;
	  c->next = NULL;
	  last_viable = &c->next;
	  *any_viable_p = true;
	}
      else
	cand = &c->next;
    }

  return viable ? viable : cands;
}