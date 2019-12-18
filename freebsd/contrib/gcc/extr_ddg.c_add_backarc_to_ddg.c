#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ddg_ptr ;
typedef  int /*<<< orphan*/  ddg_edge_ptr ;
struct TYPE_4__ {int num_backarcs; int /*<<< orphan*/ * backarcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_edge_to_ddg (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ xrealloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
add_backarc_to_ddg (ddg_ptr g, ddg_edge_ptr e)
{
  int size = (g->num_backarcs + 1) * sizeof (ddg_edge_ptr);

  add_edge_to_ddg (g, e);
  g->backarcs = (ddg_edge_ptr *) xrealloc (g->backarcs, size);
  g->backarcs[g->num_backarcs++] = e;
}