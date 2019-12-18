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
typedef  int /*<<< orphan*/ * rtx ;
struct TYPE_4__ {TYPE_1__* eh; } ;
struct TYPE_3__ {scalar_t__ built_landing_pads; } ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ JUMP_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REG_EH_REGION ; 
 scalar_t__ RESX ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int XINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arh_to_label ; 
 int /*<<< orphan*/  arh_to_landing_pad ; 
 TYPE_2__* cfun ; 
 int /*<<< orphan*/ * find_reg_note (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  foreach_reachable_handler (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

rtx
reachable_handlers (rtx insn)
{
  bool is_resx = false;
  rtx handlers = NULL;
  int region_number;

  if (JUMP_P (insn)
      && GET_CODE (PATTERN (insn)) == RESX)
    {
      region_number = XINT (PATTERN (insn), 0);
      is_resx = true;
    }
  else
    {
      rtx note = find_reg_note (insn, REG_EH_REGION, NULL_RTX);
      if (!note || INTVAL (XEXP (note, 0)) <= 0)
	return NULL;
      region_number = INTVAL (XEXP (note, 0));
    }

  foreach_reachable_handler (region_number, is_resx,
			     (cfun->eh->built_landing_pads
			      ? arh_to_landing_pad
			      : arh_to_label),
			     &handlers);

  return handlers;
}