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
struct loop {int /*<<< orphan*/  latch; } ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_2__ {struct loop* loop_father; } ;

/* Variables and functions */
 size_t CDI_DOMINATORS ; 
 int /*<<< orphan*/  add_bb_to_loop (int /*<<< orphan*/ ,struct loop*) ; 
 scalar_t__* dom_computed ; 
 int /*<<< orphan*/  set_immediate_dominator (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  single_pred (int /*<<< orphan*/ ) ; 
 TYPE_1__* single_succ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mfb_update_loops (basic_block jump)
{
  struct loop *loop = single_succ (jump)->loop_father;

  if (dom_computed[CDI_DOMINATORS])
    set_immediate_dominator (CDI_DOMINATORS, jump, single_pred (jump));
  add_bb_to_loop (jump, loop);
  loop->latch = jump;
}