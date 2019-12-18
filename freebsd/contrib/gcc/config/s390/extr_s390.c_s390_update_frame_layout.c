#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* machine; } ;
struct TYPE_3__ {scalar_t__ base_reg; } ;

/* Variables and functions */
 size_t BASE_REGNUM ; 
 size_t REGNO (scalar_t__) ; 
 size_t RETURN_REGNUM ; 
 size_t STACK_POINTER_REGNUM ; 
 TYPE_2__* cfun ; 
 int* regs_ever_live ; 
 int /*<<< orphan*/  s390_register_info (int*) ; 

__attribute__((used)) static void
s390_update_frame_layout (void)
{
  int clobbered_regs[16];

  s390_register_info (clobbered_regs);

  regs_ever_live[BASE_REGNUM] = clobbered_regs[BASE_REGNUM];
  regs_ever_live[RETURN_REGNUM] = clobbered_regs[RETURN_REGNUM];
  regs_ever_live[STACK_POINTER_REGNUM] = clobbered_regs[STACK_POINTER_REGNUM];

  if (cfun->machine->base_reg)
    regs_ever_live[REGNO (cfun->machine->base_reg)] = 1;
}