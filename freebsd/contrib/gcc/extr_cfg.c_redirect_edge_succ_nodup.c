#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_7__ {scalar_t__ probability; scalar_t__ count; int /*<<< orphan*/  flags; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 scalar_t__ REG_BR_PROB_BASE ; 
 TYPE_1__* find_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redirect_edge_succ (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_edge (TYPE_1__*) ; 

edge
redirect_edge_succ_nodup (edge e, basic_block new_succ)
{
  edge s;

  s = find_edge (e->src, new_succ);
  if (s && s != e)
    {
      s->flags |= e->flags;
      s->probability += e->probability;
      if (s->probability > REG_BR_PROB_BASE)
	s->probability = REG_BR_PROB_BASE;
      s->count += e->count;
      remove_edge (e);
      e = s;
    }
  else
    redirect_edge_succ (e, new_succ);

  return e;
}