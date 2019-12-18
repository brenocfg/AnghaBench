#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_5__ {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  connect_src (TYPE_1__*) ; 
 int /*<<< orphan*/  disconnect_src (TYPE_1__*) ; 

void
redirect_edge_pred (edge e, basic_block new_pred)
{
  disconnect_src (e);

  e->src = new_pred;

  /* Reconnect the edge to the new predecessor block.  */
  connect_src (e);
}