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
struct TYPE_3__ {int done; int /*<<< orphan*/  phi_stmt; scalar_t__ num_phi; scalar_t__ phi_i; int /*<<< orphan*/  iter_type; int /*<<< orphan*/ * mustkills; int /*<<< orphan*/ * mustdefs; int /*<<< orphan*/ * mayuses; int /*<<< orphan*/ * maydefs; int /*<<< orphan*/ * vuses; int /*<<< orphan*/ * uses; int /*<<< orphan*/ * defs; } ;
typedef  TYPE_1__ ssa_op_iter ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  ssa_op_iter_none ; 

__attribute__((used)) static inline void
clear_and_done_ssa_iter (ssa_op_iter *ptr)
{
  ptr->defs = NULL;
  ptr->uses = NULL;
  ptr->vuses = NULL;
  ptr->maydefs = NULL;
  ptr->mayuses = NULL;
  ptr->mustdefs = NULL;
  ptr->mustkills = NULL;
  ptr->iter_type = ssa_op_iter_none;
  ptr->phi_i = 0;
  ptr->num_phi = 0;
  ptr->phi_stmt = NULL_TREE;
  ptr->done = true;
}