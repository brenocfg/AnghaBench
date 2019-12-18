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
struct loops {int /*<<< orphan*/ ** parray; } ;
struct loop {unsigned int num_nodes; size_t num; int /*<<< orphan*/  outer; int /*<<< orphan*/  inner; } ;
typedef  TYPE_1__* basic_block ;
struct TYPE_3__ {int /*<<< orphan*/  loop_father; } ;

/* Variables and functions */
 int /*<<< orphan*/  flow_loop_free (struct loop*) ; 
 int /*<<< orphan*/  flow_loop_tree_node_remove (struct loop*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__** get_loop_body (struct loop*) ; 

__attribute__((used)) static void
cancel_loop (struct loops *loops, struct loop *loop)
{
  basic_block *bbs;
  unsigned i;

  gcc_assert (!loop->inner);

  /* Move blocks up one level (they should be removed as soon as possible).  */
  bbs = get_loop_body (loop);
  for (i = 0; i < loop->num_nodes; i++)
    bbs[i]->loop_father = loop->outer;

  /* Remove the loop from structure.  */
  flow_loop_tree_node_remove (loop);

  /* Remove loop from loops array.  */
  loops->parray[loop->num] = NULL;

  /* Free loop data.  */
  flow_loop_free (loop);
}