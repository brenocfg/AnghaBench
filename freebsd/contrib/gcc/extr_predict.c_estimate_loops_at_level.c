#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct loop {unsigned int num_nodes; TYPE_1__* latch; struct loop* inner; struct loop* next; } ;
typedef  int /*<<< orphan*/  edge ;
typedef  int /*<<< orphan*/  bitmap ;
typedef  TYPE_2__* basic_block ;
struct TYPE_8__ {int back_edge; } ;
struct TYPE_7__ {int /*<<< orphan*/  index; } ;
struct TYPE_6__ {int /*<<< orphan*/  succs; } ;

/* Variables and functions */
 scalar_t__ EDGE_COUNT (int /*<<< orphan*/ ) ; 
 TYPE_5__* EDGE_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__**) ; 
 TYPE_2__** get_loop_body (struct loop*) ; 
 int /*<<< orphan*/  loop_latch_edge (struct loop*) ; 
 int /*<<< orphan*/  propagate_freq (struct loop*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
estimate_loops_at_level (struct loop *first_loop, bitmap tovisit)
{
  struct loop *loop;

  for (loop = first_loop; loop; loop = loop->next)
    {
      edge e;
      basic_block *bbs;
      unsigned i;

      estimate_loops_at_level (loop->inner, tovisit);

      /* Do not do this for dummy function loop.  */
      if (EDGE_COUNT (loop->latch->succs) > 0)
	{
	  /* Find current loop back edge and mark it.  */
	  e = loop_latch_edge (loop);
	  EDGE_INFO (e)->back_edge = 1;
       }

      bbs = get_loop_body (loop);
      for (i = 0; i < loop->num_nodes; i++)
	bitmap_set_bit (tovisit, bbs[i]->index);
      free (bbs);
      propagate_freq (loop, tovisit);
    }
}