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
typedef  scalar_t__ rtx ;
struct TYPE_4__ {TYPE_1__* machine; } ;
struct TYPE_3__ {int all_noreorder_p; } ;

/* Variables and functions */
 scalar_t__ ASM_INPUT ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
#define  HAZARD_DELAY 130 
#define  HAZARD_HILO 129 
#define  HAZARD_NONE 128 
 scalar_t__ INSN_CODE (scalar_t__) ; 
 int /*<<< orphan*/  INSN_P (scalar_t__) ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ asm_noperands (scalar_t__) ; 
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  emit_insn_after (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_hazard_nop () ; 
 int get_attr_hazard (scalar_t__) ; 
 int get_attr_length (scalar_t__) ; 
 scalar_t__ reg_referenced_p (scalar_t__,scalar_t__) ; 
 scalar_t__ reg_set_p (scalar_t__,scalar_t__) ; 
 scalar_t__ single_set (scalar_t__) ; 

__attribute__((used)) static void
mips_avoid_hazard (rtx after, rtx insn, int *hilo_delay,
		   rtx *delayed_reg, rtx lo_reg)
{
  rtx pattern, set;
  int nops, ninsns;

  if (!INSN_P (insn))
    return;

  pattern = PATTERN (insn);

  /* Do not put the whole function in .set noreorder if it contains
     an asm statement.  We don't know whether there will be hazards
     between the asm statement and the gcc-generated code.  */
  if (GET_CODE (pattern) == ASM_INPUT || asm_noperands (pattern) >= 0)
    cfun->machine->all_noreorder_p = false;

  /* Ignore zero-length instructions (barriers and the like).  */
  ninsns = get_attr_length (insn) / 4;
  if (ninsns == 0)
    return;

  /* Work out how many nops are needed.  Note that we only care about
     registers that are explicitly mentioned in the instruction's pattern.
     It doesn't matter that calls use the argument registers or that they
     clobber hi and lo.  */
  if (*hilo_delay < 2 && reg_set_p (lo_reg, pattern))
    nops = 2 - *hilo_delay;
  else if (*delayed_reg != 0 && reg_referenced_p (*delayed_reg, pattern))
    nops = 1;
  else
    nops = 0;

  /* Insert the nops between this instruction and the previous one.
     Each new nop takes us further from the last hilo hazard.  */
  *hilo_delay += nops;
  while (nops-- > 0)
    emit_insn_after (gen_hazard_nop (), after);

  /* Set up the state for the next instruction.  */
  *hilo_delay += ninsns;
  *delayed_reg = 0;
  if (INSN_CODE (insn) >= 0)
    switch (get_attr_hazard (insn))
      {
      case HAZARD_NONE:
	break;

      case HAZARD_HILO:
	*hilo_delay = 0;
	break;

      case HAZARD_DELAY:
	set = single_set (insn);
	gcc_assert (set != 0);
	*delayed_reg = SET_DEST (set);
	break;
      }
}