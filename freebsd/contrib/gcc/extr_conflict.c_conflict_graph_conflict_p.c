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
struct conflict_graph_arc_def {int /*<<< orphan*/  larger; int /*<<< orphan*/  smaller; } ;
typedef  TYPE_1__* conflict_graph ;
struct TYPE_3__ {int /*<<< orphan*/  arc_hash_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int,int) ; 
 int /*<<< orphan*/  MIN (int,int) ; 
 int /*<<< orphan*/ * htab_find (int /*<<< orphan*/ ,void*) ; 

int
conflict_graph_conflict_p (conflict_graph graph, int reg1, int reg2)
{
  /* Build an arc to search for.  */
  struct conflict_graph_arc_def arc;
  arc.smaller = MIN (reg1, reg2);
  arc.larger = MAX (reg1, reg2);

  return htab_find (graph->arc_hash_table, (void *) &arc) != NULL;
}