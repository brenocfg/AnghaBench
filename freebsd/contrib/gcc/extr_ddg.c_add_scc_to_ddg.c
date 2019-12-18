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
typedef  int /*<<< orphan*/  ddg_scc_ptr ;
typedef  TYPE_1__* ddg_all_sccs_ptr ;
struct TYPE_3__ {int num_sccs; int /*<<< orphan*/ * sccs; } ;

/* Variables and functions */
 scalar_t__ xrealloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
add_scc_to_ddg (ddg_all_sccs_ptr g, ddg_scc_ptr scc)
{
  int size = (g->num_sccs + 1) * sizeof (ddg_scc_ptr);

  g->sccs = (ddg_scc_ptr *) xrealloc (g->sccs, size);
  g->sccs[g->num_sccs++] = scc;
}