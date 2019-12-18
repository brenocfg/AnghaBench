#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* const_conflict_graph_arc ;
struct TYPE_2__ {scalar_t__ smaller; scalar_t__ larger; } ;

/* Variables and functions */

__attribute__((used)) static int
arc_eq (const void *arcp1, const void *arcp2)
{
  const_conflict_graph_arc arc1 = (const_conflict_graph_arc) arcp1;
  const_conflict_graph_arc arc2 = (const_conflict_graph_arc) arcp2;

  return arc1->smaller == arc2->smaller && arc1->larger == arc2->larger;
}