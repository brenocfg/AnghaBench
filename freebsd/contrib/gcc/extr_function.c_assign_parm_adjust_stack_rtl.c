#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct assign_parm_data_one {scalar_t__ nominal_mode; scalar_t__ passed_mode; int /*<<< orphan*/ * stack_parm; scalar_t__ nominal_type; scalar_t__ passed_pointer; int /*<<< orphan*/ * entry_parm; } ;
typedef  int /*<<< orphan*/ * rtx ;
struct TYPE_2__ {scalar_t__ stack_protect_guard; } ;

/* Variables and functions */
 scalar_t__ BLKmode ; 
 scalar_t__ GET_MODE_ALIGNMENT (scalar_t__) ; 
 scalar_t__ MEM_ALIGN (int /*<<< orphan*/ *) ; 
 scalar_t__ POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ PREFERRED_STACK_BOUNDARY ; 
 scalar_t__ STRICT_ALIGNMENT ; 
 scalar_t__ TYPE_ALIGN (scalar_t__) ; 
 TYPE_1__* cfun ; 
 int flag_stack_protect ; 

__attribute__((used)) static void
assign_parm_adjust_stack_rtl (struct assign_parm_data_one *data)
{
  rtx stack_parm = data->stack_parm;

  /* If we can't trust the parm stack slot to be aligned enough for its
     ultimate type, don't use that slot after entry.  We'll make another
     stack slot, if we need one.  */
  if (stack_parm
      && ((STRICT_ALIGNMENT
	   && GET_MODE_ALIGNMENT (data->nominal_mode) > MEM_ALIGN (stack_parm))
	  || (data->nominal_type
	      && TYPE_ALIGN (data->nominal_type) > MEM_ALIGN (stack_parm)
	      && MEM_ALIGN (stack_parm) < PREFERRED_STACK_BOUNDARY)))
    stack_parm = NULL;

  /* If parm was passed in memory, and we need to convert it on entry,
     don't store it back in that same slot.  */
  else if (data->entry_parm == stack_parm
	   && data->nominal_mode != BLKmode
	   && data->nominal_mode != data->passed_mode)
    stack_parm = NULL;

  /* If stack protection is in effect for this function, don't leave any
     pointers in their passed stack slots.  */
  else if (cfun->stack_protect_guard
	   && (flag_stack_protect == 2
	       || data->passed_pointer
	       || POINTER_TYPE_P (data->nominal_type)))
    stack_parm = NULL;

  data->stack_parm = stack_parm;
}