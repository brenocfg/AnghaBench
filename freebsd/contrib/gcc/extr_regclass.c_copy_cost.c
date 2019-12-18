#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int extra_cost; struct TYPE_5__* prev_sri; } ;
typedef  TYPE_1__ secondary_reload_info ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_6__ {int (* secondary_reload ) (int,int /*<<< orphan*/ ,int,int,TYPE_1__*) ;} ;

/* Variables and functions */
 int COSTS_N_INSNS (int) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int MEMORY_MOVE_COST (int,int,int) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 int NO_REGS ; 
 int PREFERRED_RELOAD_CLASS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REGNO_REG_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SCRATCH ; 
 int*** move_cost ; 
 int stub1 (int,int /*<<< orphan*/ ,int,int,TYPE_1__*) ; 
 TYPE_2__ targetm ; 

__attribute__((used)) static int
copy_cost (rtx x, enum machine_mode mode, enum reg_class class, int to_p,
	   secondary_reload_info *prev_sri)
{
  enum reg_class secondary_class = NO_REGS;
  secondary_reload_info sri;

  /* If X is a SCRATCH, there is actually nothing to move since we are
     assuming optimal allocation.  */

  if (GET_CODE (x) == SCRATCH)
    return 0;

  /* Get the class we will actually use for a reload.  */
  class = PREFERRED_RELOAD_CLASS (x, class);

  /* If we need a secondary reload for an intermediate, the
     cost is that to load the input into the intermediate register, then
     to copy it.  */

  sri.prev_sri = prev_sri;
  sri.extra_cost = 0;
  secondary_class = targetm.secondary_reload (to_p, x, class, mode, &sri);

  if (secondary_class != NO_REGS)
    return (move_cost[mode][(int) secondary_class][(int) class]
	    + sri.extra_cost
	    + copy_cost (x, mode, secondary_class, to_p, &sri));

  /* For memory, use the memory move cost, for (hard) registers, use the
     cost to move between the register classes, and use 2 for everything
     else (constants).  */

  if (MEM_P (x) || class == NO_REGS)
    return sri.extra_cost + MEMORY_MOVE_COST (mode, class, to_p);

  else if (REG_P (x))
    return (sri.extra_cost
	    + move_cost[mode][(int) REGNO_REG_CLASS (REGNO (x))][(int) class]);

  else
    /* If this is a constant, we may eventually want to call rtx_cost here.  */
    return sri.extra_cost + COSTS_N_INSNS (1);
}