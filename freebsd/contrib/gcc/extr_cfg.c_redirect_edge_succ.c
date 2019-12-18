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
struct TYPE_7__ {int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  connect_dest (TYPE_1__*) ; 
 int /*<<< orphan*/  disconnect_dest (TYPE_1__*) ; 
 int /*<<< orphan*/  execute_on_growing_pred (TYPE_1__*) ; 
 int /*<<< orphan*/  execute_on_shrinking_pred (TYPE_1__*) ; 

void
redirect_edge_succ (edge e, basic_block new_succ)
{
  execute_on_shrinking_pred (e);

  disconnect_dest (e);

  e->dest = new_succ;

  /* Reconnect the edge to the new successor block.  */
  connect_dest (e);

  execute_on_growing_pred (e);
}