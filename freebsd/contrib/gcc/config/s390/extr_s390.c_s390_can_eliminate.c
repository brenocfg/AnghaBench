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
struct TYPE_5__ {int /*<<< orphan*/  save_return_addr_p; } ;
struct TYPE_4__ {scalar_t__ base_reg; } ;

/* Variables and functions */
 int ARG_POINTER_REGNUM ; 
 int BASE_REGNUM ; 
 int FRAME_POINTER_REGNUM ; 
 int HARD_FRAME_POINTER_REGNUM ; 
 scalar_t__ NULL_RTX ; 
 int RETURN_ADDRESS_POINTER_REGNUM ; 
 int STACK_POINTER_REGNUM ; 
 scalar_t__ TARGET_CPU_ZARCH ; 
 TYPE_3__* cfun ; 
 TYPE_2__ cfun_frame_layout ; 
 int /*<<< orphan*/  current_function_calls_eh_return ; 
 int /*<<< orphan*/  current_function_stdarg ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  s390_init_frame_layout () ; 

bool
s390_can_eliminate (int from, int to)
{
  /* On zSeries machines, we have not marked the base register as fixed.
     Instead, we have an elimination rule BASE_REGNUM -> BASE_REGNUM.
     If a function requires the base register, we say here that this
     elimination cannot be performed.  This will cause reload to free
     up the base register (as if it were fixed).  On the other hand,
     if the current function does *not* require the base register, we
     say here the elimination succeeds, which in turn allows reload
     to allocate the base register for any other purpose.  */
  if (from == BASE_REGNUM && to == BASE_REGNUM)
    {
      if (TARGET_CPU_ZARCH)
	{
	  s390_init_frame_layout ();
	  return cfun->machine->base_reg == NULL_RTX;
	}

      return false;
    }

  /* Everything else must point into the stack frame.  */
  gcc_assert (to == STACK_POINTER_REGNUM
	      || to == HARD_FRAME_POINTER_REGNUM);

  gcc_assert (from == FRAME_POINTER_REGNUM
	      || from == ARG_POINTER_REGNUM
	      || from == RETURN_ADDRESS_POINTER_REGNUM);

  /* Make sure we actually saved the return address.  */
  if (from == RETURN_ADDRESS_POINTER_REGNUM)
    if (!current_function_calls_eh_return
	&& !current_function_stdarg
	&& !cfun_frame_layout.save_return_addr_p)
      return false;

  return true;
}