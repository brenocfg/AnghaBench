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
typedef  TYPE_1__* edge ;
struct TYPE_4__ {int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 scalar_t__ phi_nodes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_phi_args (TYPE_1__*) ; 

__attribute__((used)) static void
tree_execute_on_shrinking_pred (edge e)
{
  if (phi_nodes (e->dest))
    remove_phi_args (e);
}