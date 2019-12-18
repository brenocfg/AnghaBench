#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  edge_iterator ;
typedef  TYPE_1__* edge ;
typedef  TYPE_2__* basic_block ;
struct TYPE_7__ {int /*<<< orphan*/  preds; } ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int EDGE_FAKE ; 
 int /*<<< orphan*/  ei_next (int /*<<< orphan*/ *) ; 
 TYPE_1__* ei_safe_edge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ei_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_edge (TYPE_1__*) ; 

__attribute__((used)) static void
remove_fake_predecessors (basic_block bb)
{
  edge e;
  edge_iterator ei;

  for (ei = ei_start (bb->preds); (e = ei_safe_edge (ei)); )
    {
      if ((e->flags & EDGE_FAKE) == EDGE_FAKE)
	remove_edge (e);
      else
	ei_next (&ei);
    }
}