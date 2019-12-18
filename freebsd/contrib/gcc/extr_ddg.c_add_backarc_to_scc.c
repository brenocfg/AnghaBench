#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ddg_scc_ptr ;
typedef  int /*<<< orphan*/  ddg_edge_ptr ;
struct TYPE_3__ {int num_backarcs; int /*<<< orphan*/ * backarcs; } ;

/* Variables and functions */
 scalar_t__ xrealloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
add_backarc_to_scc (ddg_scc_ptr scc, ddg_edge_ptr e)
{
  int size = (scc->num_backarcs + 1) * sizeof (ddg_edge_ptr);

  scc->backarcs = (ddg_edge_ptr *) xrealloc (scc->backarcs, size);
  scc->backarcs[scc->num_backarcs++] = e;
}