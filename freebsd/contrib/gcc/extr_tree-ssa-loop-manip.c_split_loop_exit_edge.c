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
typedef  int /*<<< orphan*/  use_operand_p ;
typedef  scalar_t__ tree ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_5__ {int /*<<< orphan*/  dest; } ;
typedef  scalar_t__ SSA_NAME_DEF_STMT ;

/* Variables and functions */
 int /*<<< orphan*/  PHI_ARG_DEF_PTR_FROM_EDGE (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  SET_USE (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ USE_FROM_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_phi_arg (scalar_t__,scalar_t__,TYPE_1__*) ; 
 scalar_t__ create_phi_node (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ duplicate_ssa_name (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loop_split_edge_with (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ phi_nodes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  single_succ_edge (int /*<<< orphan*/ ) ; 

void
split_loop_exit_edge (edge exit)
{
  basic_block dest = exit->dest;
  basic_block bb = loop_split_edge_with (exit, NULL);
  tree phi, new_phi, new_name, name;
  use_operand_p op_p;

  for (phi = phi_nodes (dest); phi; phi = PHI_CHAIN (phi))
    {
      op_p = PHI_ARG_DEF_PTR_FROM_EDGE (phi, single_succ_edge (bb));

      name = USE_FROM_PTR (op_p);

      /* If the argument of the phi node is a constant, we do not need
	 to keep it inside loop.  */
      if (TREE_CODE (name) != SSA_NAME)
	continue;

      /* Otherwise create an auxiliary phi node that will copy the value
	 of the ssa name out of the loop.  */
      new_name = duplicate_ssa_name (name, NULL);
      new_phi = create_phi_node (new_name, bb);
      SSA_NAME_DEF_STMT (new_name) = new_phi;
      add_phi_arg (new_phi, name, exit);
      SET_USE (op_p, new_name);
    }
}