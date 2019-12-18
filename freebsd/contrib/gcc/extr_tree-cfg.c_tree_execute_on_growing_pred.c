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
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_3__ {int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 scalar_t__ phi_nodes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reserve_phi_args_for_new_edge (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tree_execute_on_growing_pred (edge e)
{
  basic_block bb = e->dest;

  if (phi_nodes (bb))
    reserve_phi_args_for_new_edge (bb);
}