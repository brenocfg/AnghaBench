#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  enum can_compare_purpose { ____Placeholder_can_compare_purpose } can_compare_purpose ;
struct TYPE_16__ {TYPE_1__* handlers; } ;
struct TYPE_15__ {TYPE_2__* handlers; } ;
struct TYPE_14__ {TYPE_4__* handlers; } ;
struct TYPE_13__ {TYPE_3__* handlers; } ;
struct TYPE_12__ {scalar_t__ insn_code; } ;
struct TYPE_11__ {scalar_t__ insn_code; } ;
struct TYPE_10__ {scalar_t__ insn_code; } ;
struct TYPE_9__ {scalar_t__ insn_code; } ;

/* Variables and functions */
 scalar_t__ CODE_FOR_nothing ; 
 int GET_MODE_WIDER_MODE (int) ; 
 int VOIDmode ; 
 int /*<<< orphan*/ ** bcc_gen_fctn ; 
 TYPE_8__* cbranch_optab ; 
 int ccp_cmov ; 
 int ccp_jump ; 
 int ccp_store_flag ; 
 TYPE_7__* cmov_optab ; 
 TYPE_6__* cmp_optab ; 
 TYPE_5__* cstore_optab ; 
 scalar_t__* setcc_gen_code ; 

int
can_compare_p (enum rtx_code code, enum machine_mode mode,
	       enum can_compare_purpose purpose)
{
  do
    {
      if (cmp_optab->handlers[(int) mode].insn_code != CODE_FOR_nothing)
	{
	  if (purpose == ccp_jump)
	    return bcc_gen_fctn[(int) code] != NULL;
	  else if (purpose == ccp_store_flag)
	    return setcc_gen_code[(int) code] != CODE_FOR_nothing;
	  else
	    /* There's only one cmov entry point, and it's allowed to fail.  */
	    return 1;
	}
      if (purpose == ccp_jump
	  && cbranch_optab->handlers[(int) mode].insn_code != CODE_FOR_nothing)
	return 1;
      if (purpose == ccp_cmov
	  && cmov_optab->handlers[(int) mode].insn_code != CODE_FOR_nothing)
	return 1;
      if (purpose == ccp_store_flag
	  && cstore_optab->handlers[(int) mode].insn_code != CODE_FOR_nothing)
	return 1;
      mode = GET_MODE_WIDER_MODE (mode);
    }
  while (mode != VOIDmode);

  return 0;
}