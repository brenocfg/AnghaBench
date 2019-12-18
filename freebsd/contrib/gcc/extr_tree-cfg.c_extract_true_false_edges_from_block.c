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
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 TYPE_1__* EDGE_SUCC (int /*<<< orphan*/ ,int) ; 
 int EDGE_TRUE_VALUE ; 

void
extract_true_false_edges_from_block (basic_block b,
				     edge *true_edge,
				     edge *false_edge)
{
  edge e = EDGE_SUCC (b, 0);

  if (e->flags & EDGE_TRUE_VALUE)
    {
      *true_edge = e;
      *false_edge = EDGE_SUCC (b, 1);
    }
  else
    {
      *false_edge = e;
      *true_edge = EDGE_SUCC (b, 1);
    }
}