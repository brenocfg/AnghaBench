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
struct TYPE_3__ {int ignore_hazard_length_p; int all_noreorder_p; } ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 int /*<<< orphan*/  ISA_HAS_MACCHI ; 
 int /*<<< orphan*/  LO_REGNUM ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 scalar_t__ SEQUENCE ; 
 int /*<<< orphan*/  SImode ; 
 scalar_t__ TARGET_FIX_VR4120 ; 
 scalar_t__ TARGET_FIX_VR4130 ; 
 scalar_t__ XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* cfun ; 
 scalar_t__ current_function_profile ; 
 scalar_t__ gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_insns () ; 
 int /*<<< orphan*/  mips_avoid_hazard (scalar_t__,scalar_t__,int*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  shorten_branches (scalar_t__) ; 
 int /*<<< orphan*/  split_all_insns_noflow () ; 

__attribute__((used)) static void
mips_avoid_hazards (void)
{
  rtx insn, last_insn, lo_reg, delayed_reg;
  int hilo_delay, i;

  /* Force all instructions to be split into their final form.  */
  split_all_insns_noflow ();

  /* Recalculate instruction lengths without taking nops into account.  */
  cfun->machine->ignore_hazard_length_p = true;
  shorten_branches (get_insns ());

  cfun->machine->all_noreorder_p = true;

  /* Profiled functions can't be all noreorder because the profiler
     support uses assembler macros.  */
  if (current_function_profile)
    cfun->machine->all_noreorder_p = false;

  /* Code compiled with -mfix-vr4120 can't be all noreorder because
     we rely on the assembler to work around some errata.  */
  if (TARGET_FIX_VR4120)
    cfun->machine->all_noreorder_p = false;

  /* The same is true for -mfix-vr4130 if we might generate mflo or
     mfhi instructions.  Note that we avoid using mflo and mfhi if
     the VR4130 macc and dmacc instructions are available instead;
     see the *mfhilo_{si,di}_macc patterns.  */
  if (TARGET_FIX_VR4130 && !ISA_HAS_MACCHI)
    cfun->machine->all_noreorder_p = false;

  last_insn = 0;
  hilo_delay = 2;
  delayed_reg = 0;
  lo_reg = gen_rtx_REG (SImode, LO_REGNUM);

  for (insn = get_insns (); insn != 0; insn = NEXT_INSN (insn))
    if (INSN_P (insn))
      {
	if (GET_CODE (PATTERN (insn)) == SEQUENCE)
	  for (i = 0; i < XVECLEN (PATTERN (insn), 0); i++)
	    mips_avoid_hazard (last_insn, XVECEXP (PATTERN (insn), 0, i),
			       &hilo_delay, &delayed_reg, lo_reg);
	else
	  mips_avoid_hazard (last_insn, insn, &hilo_delay,
			     &delayed_reg, lo_reg);

	last_insn = insn;
      }
}