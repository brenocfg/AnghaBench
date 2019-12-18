#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int icode; int /*<<< orphan*/ * prev_sri; } ;
typedef  TYPE_1__ secondary_reload_info ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  enum insn_code { ____Placeholder_insn_code } insn_code ;
struct TYPE_5__ {int (* secondary_reload ) (int,int /*<<< orphan*/ ,int,int,TYPE_1__*) ;} ;

/* Variables and functions */
 int CODE_FOR_nothing ; 
 int NO_REGS ; 
 int scratch_reload_class (int) ; 
 int stub1 (int,int /*<<< orphan*/ ,int,int,TYPE_1__*) ; 
 TYPE_2__ targetm ; 

enum reg_class
secondary_reload_class (bool in_p, enum reg_class class,
			enum machine_mode mode, rtx x)
{
  enum insn_code icode;
  secondary_reload_info sri;

  sri.icode = CODE_FOR_nothing;
  sri.prev_sri = NULL;
  class = targetm.secondary_reload (in_p, x, class, mode, &sri);
  icode = sri.icode;

  /* If there are no secondary reloads at all, we return NO_REGS.
     If an intermediate register is needed, we return its class.  */
  if (icode == CODE_FOR_nothing || class != NO_REGS)
    return class;

  /* No intermediate register is needed, but we have a special reload
     pattern, which we assume for now needs a scratch register.  */
  return scratch_reload_class (icode);
}