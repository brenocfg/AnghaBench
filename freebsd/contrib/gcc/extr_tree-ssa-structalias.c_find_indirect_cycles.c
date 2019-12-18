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
struct scc_info {int /*<<< orphan*/  visited; } ;
typedef  TYPE_1__* constraint_graph_t ;
struct TYPE_4__ {unsigned int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAST_REF_NODE ; 
 unsigned int MIN (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  TEST_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int find (unsigned int) ; 
 int /*<<< orphan*/  free_scc_info (struct scc_info*) ; 
 struct scc_info* init_scc_info (unsigned int) ; 
 int /*<<< orphan*/  scc_visit (TYPE_1__*,struct scc_info*,unsigned int) ; 

__attribute__((used)) static void
find_indirect_cycles (constraint_graph_t graph)
{
  unsigned int i;
  unsigned int size = graph->size;
  struct scc_info *si = init_scc_info (size);

  for (i = 0; i < MIN (LAST_REF_NODE, size); i ++ )
    if (!TEST_BIT (si->visited, i) && find (i) == i)
      scc_visit (graph, si, i);

  free_scc_info (si);
}