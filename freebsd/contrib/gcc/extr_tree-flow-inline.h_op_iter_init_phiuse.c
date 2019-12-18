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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_5__ {int done; int /*<<< orphan*/  iter_type; int /*<<< orphan*/  num_phi; int /*<<< orphan*/  phi_stmt; } ;
typedef  TYPE_1__ ssa_op_iter ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_USE_OPERAND_P ; 
 int /*<<< orphan*/  PHI_NUM_ARGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHI_RESULT (int /*<<< orphan*/ ) ; 
 int SSA_OP_USE ; 
 int SSA_OP_VIRTUAL_USES ; 
 int /*<<< orphan*/  clear_and_done_ssa_iter (TYPE_1__*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ is_gimple_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op_iter_next_use (TYPE_1__*) ; 
 int /*<<< orphan*/  ssa_op_iter_use ; 

__attribute__((used)) static inline use_operand_p
op_iter_init_phiuse (ssa_op_iter *ptr, tree phi, int flags)
{
  tree phi_def = PHI_RESULT (phi);
  int comp;

  clear_and_done_ssa_iter (ptr);
  ptr->done = false;

  gcc_assert ((flags & (SSA_OP_USE | SSA_OP_VIRTUAL_USES)) != 0);

  comp = (is_gimple_reg (phi_def) ? SSA_OP_USE : SSA_OP_VIRTUAL_USES);
    
  /* If the PHI node doesn't the operand type we care about, we're done.  */
  if ((flags & comp) == 0)
    {
      ptr->done = true;
      return NULL_USE_OPERAND_P;
    }

  ptr->phi_stmt = phi;
  ptr->num_phi = PHI_NUM_ARGS (phi);
  ptr->iter_type = ssa_op_iter_use;
  return op_iter_next_use (ptr);
}