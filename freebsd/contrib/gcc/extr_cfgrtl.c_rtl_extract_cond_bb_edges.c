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
 int EDGE_FALLTHRU ; 
 TYPE_1__* EDGE_SUCC (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rtl_extract_cond_bb_edges (basic_block b, edge *branch_edge,
			   edge *fallthru_edge)
{
  edge e = EDGE_SUCC (b, 0);

  if (e->flags & EDGE_FALLTHRU)
    {
      *fallthru_edge = e;
      *branch_edge = EDGE_SUCC (b, 1);
    }
  else
    {
      *branch_edge = e;
      *fallthru_edge = EDGE_SUCC (b, 1);
    }
}