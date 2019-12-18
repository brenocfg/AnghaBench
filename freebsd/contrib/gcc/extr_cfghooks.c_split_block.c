#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * edge ;
typedef  TYPE_1__* basic_block ;
struct TYPE_13__ {int /*<<< orphan*/  loop_depth; int /*<<< orphan*/  frequency; int /*<<< orphan*/  count; } ;
struct TYPE_12__ {TYPE_1__* (* split_block ) (TYPE_1__*,void*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 int /*<<< orphan*/  EDGE_FALLTHRU ; 
 TYPE_11__* cfg_hooks ; 
 scalar_t__ dom_info_available_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  internal_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * make_single_succ_edge (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redirect_immediate_dominators (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  set_immediate_dominator (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* stub1 (TYPE_1__*,void*) ; 

edge
split_block (basic_block bb, void *i)
{
  basic_block new_bb;

  if (!cfg_hooks->split_block)
    internal_error ("%s does not support split_block", cfg_hooks->name);

  new_bb = cfg_hooks->split_block (bb, i);
  if (!new_bb)
    return NULL;

  new_bb->count = bb->count;
  new_bb->frequency = bb->frequency;
  new_bb->loop_depth = bb->loop_depth;

  if (dom_info_available_p (CDI_DOMINATORS))
    {
      redirect_immediate_dominators (CDI_DOMINATORS, bb, new_bb);
      set_immediate_dominator (CDI_DOMINATORS, new_bb, bb);
    }

  return make_single_succ_edge (bb, new_bb, EDGE_FALLTHRU);
}