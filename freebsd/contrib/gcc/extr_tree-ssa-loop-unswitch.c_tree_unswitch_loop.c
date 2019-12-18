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
typedef  int /*<<< orphan*/  tree ;
struct loops {int dummy; } ;
struct loop {int /*<<< orphan*/ * inner; } ;
typedef  TYPE_1__* basic_block ;
struct TYPE_5__ {int /*<<< orphan*/  succs; } ;

/* Variables and functions */
 int EDGE_COUNT (int /*<<< orphan*/ ) ; 
 int flow_bb_inside_loop_p (struct loop*,TYPE_1__*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 struct loop* loop_version (struct loops*,struct loop*,int /*<<< orphan*/ ,TYPE_1__**,int) ; 
 int /*<<< orphan*/  unshare_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct loop *
tree_unswitch_loop (struct loops *loops, struct loop *loop,
		    basic_block unswitch_on, tree cond)
{
  basic_block condition_bb;

  /* Some sanity checking.  */
  gcc_assert (flow_bb_inside_loop_p (loop, unswitch_on));
  gcc_assert (EDGE_COUNT (unswitch_on->succs) == 2);
  gcc_assert (loop->inner == NULL);

  return loop_version (loops, loop, unshare_expr (cond), 
		       &condition_bb, false);
}