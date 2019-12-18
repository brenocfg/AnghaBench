#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* edge ;
typedef  scalar_t__ basic_block ;
struct TYPE_6__ {scalar_t__ dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 int /*<<< orphan*/  EDGE_TRUE_VALUE ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ ir_type () ; 
 int /*<<< orphan*/  lv_add_condition_to_bb (scalar_t__,scalar_t__,scalar_t__,void*) ; 
 int /*<<< orphan*/  lv_adjust_loop_header_phi (scalar_t__,scalar_t__,scalar_t__,TYPE_1__*) ; 
 TYPE_1__* make_edge (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_immediate_dominator (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ split_edge (TYPE_1__*) ; 

__attribute__((used)) static basic_block
lv_adjust_loop_entry_edge (basic_block first_head,
			   basic_block second_head,
			   edge e,
			   void *cond_expr)
{
  basic_block new_head = NULL;
  edge e1;

  gcc_assert (e->dest == second_head);

  /* Split edge 'e'. This will create a new basic block, where we can
     insert conditional expr.  */
  new_head = split_edge (e);


  lv_add_condition_to_bb (first_head, second_head, new_head,
			  cond_expr);

  /* Don't set EDGE_TRUE_VALUE in RTL mode, as it's invalid there.  */
  e1 = make_edge (new_head, first_head, ir_type () ? EDGE_TRUE_VALUE : 0);
  set_immediate_dominator (CDI_DOMINATORS, first_head, new_head);
  set_immediate_dominator (CDI_DOMINATORS, second_head, new_head);

  /* Adjust loop header phi nodes.  */
  lv_adjust_loop_header_phi (first_head, second_head, new_head, e1);

  return new_head;
}