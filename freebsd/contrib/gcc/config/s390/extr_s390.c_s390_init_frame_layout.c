#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* machine; } ;
struct TYPE_5__ {scalar_t__ frame_size; } ;
struct TYPE_4__ {int split_branches_pending_p; void* base_reg; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 int BASE_REGNUM ; 
 int /*<<< orphan*/  CONST_OK_FOR_K (scalar_t__) ; 
 int /*<<< orphan*/  DISP_IN_RANGE (scalar_t__) ; 
 void* NULL_RTX ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  TARGET_CPU_ZARCH ; 
 TYPE_3__* cfun ; 
 TYPE_2__ cfun_frame_layout ; 
 scalar_t__ current_function_is_leaf ; 
 scalar_t__ current_function_uses_const_pool ; 
 void* gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * regs_ever_live ; 
 int /*<<< orphan*/  s390_frame_info () ; 
 int /*<<< orphan*/  s390_register_info (int*) ; 

__attribute__((used)) static void
s390_init_frame_layout (void)
{
  HOST_WIDE_INT frame_size;
  int base_used;
  int clobbered_regs[16];

  /* On S/390 machines, we may need to perform branch splitting, which
     will require both base and return address register.  We have no
     choice but to assume we're going to need them until right at the
     end of the machine dependent reorg phase.  */
  if (!TARGET_CPU_ZARCH)
    cfun->machine->split_branches_pending_p = true;

  do
    {
      frame_size = cfun_frame_layout.frame_size;

      /* Try to predict whether we'll need the base register.  */
      base_used = cfun->machine->split_branches_pending_p
		  || current_function_uses_const_pool
		  || (!DISP_IN_RANGE (frame_size)
		      && !CONST_OK_FOR_K (frame_size));

      /* Decide which register to use as literal pool base.  In small
	 leaf functions, try to use an unused call-clobbered register
	 as base register to avoid save/restore overhead.  */
      if (!base_used)
	cfun->machine->base_reg = NULL_RTX;
      else if (current_function_is_leaf && !regs_ever_live[5])
	cfun->machine->base_reg = gen_rtx_REG (Pmode, 5);
      else
	cfun->machine->base_reg = gen_rtx_REG (Pmode, BASE_REGNUM);

      s390_register_info (clobbered_regs);
      s390_frame_info ();
    }
  while (frame_size != cfun_frame_layout.frame_size);
}