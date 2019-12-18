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
struct TYPE_3__ {int /*<<< orphan*/  num_sccs; int /*<<< orphan*/  sccs; } ;

/* Variables and functions */
 scalar_t__ compare_sccs ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int (*) (void const*,void const*)) ; 

__attribute__((used)) static void
order_sccs (ddg_all_sccs_ptr g)
{
  qsort (g->sccs, g->num_sccs, sizeof (ddg_scc_ptr),
	 (int (*) (const void *, const void *)) compare_sccs);
}