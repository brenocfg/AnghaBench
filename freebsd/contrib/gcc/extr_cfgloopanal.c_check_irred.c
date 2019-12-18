#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct graph {TYPE_1__* vertices; } ;
struct edge {size_t src; size_t dest; TYPE_3__* data; } ;
typedef  TYPE_3__* edge ;
struct TYPE_6__ {TYPE_2__* src; int /*<<< orphan*/  dest; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  loop_father; } ;
struct TYPE_4__ {scalar_t__ component; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_IRREDUCIBLE_LOOP ; 
 int /*<<< orphan*/  EDGE_IRREDUCIBLE_LOOP ; 
 scalar_t__ flow_bb_inside_loop_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static void
check_irred (struct graph *g, struct edge *e)
{
  edge real = e->data;

  /* All edges should lead from a component with higher number to the
     one with lower one.  */
  gcc_assert (g->vertices[e->src].component >= g->vertices[e->dest].component);

  if (g->vertices[e->src].component != g->vertices[e->dest].component)
    return;

  real->flags |= EDGE_IRREDUCIBLE_LOOP;
  if (flow_bb_inside_loop_p (real->src->loop_father, real->dest))
    real->src->flags |= BB_IRREDUCIBLE_LOOP;
}