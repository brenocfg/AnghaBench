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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {int done; int /*<<< orphan*/  phi_stmt; scalar_t__ num_phi; scalar_t__ phi_i; int /*<<< orphan*/ * mustkills; int /*<<< orphan*/ * mustdefs; int /*<<< orphan*/ * mayuses; int /*<<< orphan*/ * maydefs; int /*<<< orphan*/ * vuses; int /*<<< orphan*/ * uses; int /*<<< orphan*/ * defs; } ;
typedef  TYPE_1__ ssa_op_iter ;

/* Variables and functions */
 int /*<<< orphan*/ * DEF_OPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MAYDEF_OPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MUSTDEF_OPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int SSA_OP_DEF ; 
 int SSA_OP_USE ; 
 int SSA_OP_VMAYDEF ; 
 int SSA_OP_VMAYUSE ; 
 int SSA_OP_VMUSTDEF ; 
 int SSA_OP_VMUSTKILL ; 
 int SSA_OP_VUSE ; 
 int /*<<< orphan*/ * USE_OPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * VUSE_OPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmt_ann (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
op_iter_init (ssa_op_iter *ptr, tree stmt, int flags)
{
#ifdef ENABLE_CHECKING
  gcc_assert (stmt_ann (stmt));
#endif

  ptr->defs = (flags & SSA_OP_DEF) ? DEF_OPS (stmt) : NULL;
  ptr->uses = (flags & SSA_OP_USE) ? USE_OPS (stmt) : NULL;
  ptr->vuses = (flags & SSA_OP_VUSE) ? VUSE_OPS (stmt) : NULL;
  ptr->maydefs = (flags & SSA_OP_VMAYDEF) ? MAYDEF_OPS (stmt) : NULL;
  ptr->mayuses = (flags & SSA_OP_VMAYUSE) ? MAYDEF_OPS (stmt) : NULL;
  ptr->mustdefs = (flags & SSA_OP_VMUSTDEF) ? MUSTDEF_OPS (stmt) : NULL;
  ptr->mustkills = (flags & SSA_OP_VMUSTKILL) ? MUSTDEF_OPS (stmt) : NULL;
  ptr->done = false;

  ptr->phi_i = 0;
  ptr->num_phi = 0;
  ptr->phi_stmt = NULL_TREE;
}