#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct loops {int /*<<< orphan*/ ** parray; } ;
struct loop {unsigned int num_nodes; size_t num; int /*<<< orphan*/  outer; struct loop* inner; TYPE_1__* latch; } ;
typedef  TYPE_1__* basic_block ;
struct TYPE_10__ {int flags; } ;
struct TYPE_9__ {struct loop* loop_father; } ;

/* Variables and functions */
 int EDGE_IRREDUCIBLE_LOOP ; 
 int /*<<< orphan*/  add_bb_to_loop (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fix_bb_placements (struct loops*,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  flow_loop_free (struct loop*) ; 
 int /*<<< orphan*/  flow_loop_tree_node_add (int /*<<< orphan*/ ,struct loop*) ; 
 int /*<<< orphan*/  flow_loop_tree_node_remove (struct loop*) ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 TYPE_1__** get_loop_body (struct loop*) ; 
 TYPE_4__* loop_preheader_edge (struct loop*) ; 
 int /*<<< orphan*/  remove_bb_from_loops (TYPE_1__*) ; 
 int /*<<< orphan*/  remove_edge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  single_succ_edge (TYPE_1__*) ; 

__attribute__((used)) static void
unloop (struct loops *loops, struct loop *loop, bool *irred_invalidated)
{
  basic_block *body;
  struct loop *ploop;
  unsigned i, n;
  basic_block latch = loop->latch;
  bool dummy = false;

  if (loop_preheader_edge (loop)->flags & EDGE_IRREDUCIBLE_LOOP)
    *irred_invalidated = true;

  /* This is relatively straightforward.  The dominators are unchanged, as
     loop header dominates loop latch, so the only thing we have to care of
     is the placement of loops and basic blocks inside the loop tree.  We
     move them all to the loop->outer, and then let fix_bb_placements do
     its work.  */

  body = get_loop_body (loop);
  n = loop->num_nodes;
  for (i = 0; i < n; i++)
    if (body[i]->loop_father == loop)
      {
	remove_bb_from_loops (body[i]);
	add_bb_to_loop (body[i], loop->outer);
      }
  free(body);

  while (loop->inner)
    {
      ploop = loop->inner;
      flow_loop_tree_node_remove (ploop);
      flow_loop_tree_node_add (loop->outer, ploop);
    }

  /* Remove the loop and free its data.  */
  flow_loop_tree_node_remove (loop);
  loops->parray[loop->num] = NULL;
  flow_loop_free (loop);

  remove_edge (single_succ_edge (latch));

  /* We do not pass IRRED_INVALIDATED to fix_bb_placements here, as even if
     there is an irreducible region inside the cancelled loop, the flags will
     be still correct.  */
  fix_bb_placements (loops, latch, &dummy);
}