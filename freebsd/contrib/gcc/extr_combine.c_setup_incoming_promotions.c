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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_6__ {int /*<<< orphan*/  decl; } ;
struct TYPE_4__ {scalar_t__ (* promote_function_args ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ calls; } ;

/* Variables and functions */
 unsigned int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ FUNCTION_ARG_REGNO_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTGOING_REGNO (unsigned int) ; 
 int /*<<< orphan*/  SIGN_EXTEND ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZERO_EXTEND ; 
 TYPE_3__* cfun ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  gen_rtx_CLOBBER (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_fmt_e (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  promoted_input_arg (unsigned int,int*,int*) ; 
 int /*<<< orphan*/  record_value_for_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 

__attribute__((used)) static void
setup_incoming_promotions (void)
{
  unsigned int regno;
  rtx reg;
  enum machine_mode mode;
  int unsignedp;
  rtx first = get_insns ();

  if (targetm.calls.promote_function_args (TREE_TYPE (cfun->decl)))
    {
      for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)
	/* Check whether this register can hold an incoming pointer
	   argument.  FUNCTION_ARG_REGNO_P tests outgoing register
	   numbers, so translate if necessary due to register windows.  */
	if (FUNCTION_ARG_REGNO_P (OUTGOING_REGNO (regno))
	    && (reg = promoted_input_arg (regno, &mode, &unsignedp)) != 0)
	  {
	    record_value_for_reg
	      (reg, first, gen_rtx_fmt_e ((unsignedp ? ZERO_EXTEND
					   : SIGN_EXTEND),
					  GET_MODE (reg),
					  gen_rtx_CLOBBER (mode, const0_rtx)));
	  }
    }
}