#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct topo_info {int /*<<< orphan*/  visited; } ;
typedef  int /*<<< orphan*/  constraint_graph_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int VEC_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int find (unsigned int) ; 
 int /*<<< orphan*/  topo_visit (int /*<<< orphan*/ ,struct topo_info*,unsigned int) ; 
 int /*<<< orphan*/  varinfo_t ; 
 int /*<<< orphan*/  varmap ; 

__attribute__((used)) static void
compute_topo_order (constraint_graph_t graph,
		    struct topo_info *ti)
{
  unsigned int i;
  unsigned int size = VEC_length (varinfo_t, varmap);

  for (i = 0; i != size; ++i)
    if (!TEST_BIT (ti->visited, i) && find (i) == i)
      topo_visit (graph, ti, i);
}