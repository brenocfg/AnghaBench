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
struct TYPE_4__ {scalar_t__ var; scalar_t__ constant; } ;
struct TYPE_5__ {TYPE_1__ size; } ;
struct assign_parm_data_one {scalar_t__ partial; TYPE_2__ locate; int /*<<< orphan*/ * entry_parm; } ;
struct TYPE_6__ {int /*<<< orphan*/  constant; } ;
struct assign_parm_data_all {scalar_t__ reg_parm_stack_space; TYPE_3__ stack_args_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_PARM_SIZE (TYPE_3__,scalar_t__) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PARALLEL ; 
 scalar_t__ XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
assign_parm_is_stack_parm (struct assign_parm_data_all *all,
			   struct assign_parm_data_one *data)
{
  /* Trivially true if we've no incoming register.  */
  if (data->entry_parm == NULL)
    ;
  /* Also true if we're partially in registers and partially not,
     since we've arranged to drop the entire argument on the stack.  */
  else if (data->partial != 0)
    ;
  /* Also true if the target says that it's passed in both registers
     and on the stack.  */
  else if (GET_CODE (data->entry_parm) == PARALLEL
	   && XEXP (XVECEXP (data->entry_parm, 0, 0), 0) == NULL_RTX)
    ;
  /* Also true if the target says that there's stack allocated for
     all register parameters.  */
  else if (all->reg_parm_stack_space > 0)
    ;
  /* Otherwise, no, this parameter has no ABI defined stack slot.  */
  else
    return false;

  all->stack_args_size.constant += data->locate.size.constant;
  if (data->locate.size.var)
    ADD_PARM_SIZE (all->stack_args_size, data->locate.size.var);

  return true;
}