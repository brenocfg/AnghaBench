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
struct TYPE_3__ {scalar_t__ mips16_gp_pseudo_rtx; } ;

/* Variables and functions */
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NOTE_INSN_FUNCTION_BEG ; 
 scalar_t__ NOTE_LINE_NUMBER (scalar_t__) ; 
 scalar_t__ NOTE_P (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  UNSPEC_GP ; 
 int /*<<< orphan*/  VOIDmode ; 
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  const0_rtx ; 
 scalar_t__ emit_insn_after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 scalar_t__ gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_CONST (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_rtx_UNSPEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_insns () ; 
 int /*<<< orphan*/  pop_topmost_sequence () ; 
 int /*<<< orphan*/  push_topmost_sequence () ; 
 int /*<<< orphan*/  start_sequence () ; 

__attribute__((used)) static rtx
mips16_gp_pseudo_reg (void)
{
  if (cfun->machine->mips16_gp_pseudo_rtx == NULL_RTX)
    {
      rtx unspec;
      rtx insn, scan;

      cfun->machine->mips16_gp_pseudo_rtx = gen_reg_rtx (Pmode);

      /* We want to initialize this to a value which gcc will believe
         is constant.  */
      start_sequence ();
      unspec = gen_rtx_UNSPEC (VOIDmode, gen_rtvec (1, const0_rtx), UNSPEC_GP);
      emit_move_insn (cfun->machine->mips16_gp_pseudo_rtx,
		      gen_rtx_CONST (Pmode, unspec));
      insn = get_insns ();
      end_sequence ();

      push_topmost_sequence ();
      /* We need to emit the initialization after the FUNCTION_BEG
         note, so that it will be integrated.  */
      for (scan = get_insns (); scan != NULL_RTX; scan = NEXT_INSN (scan))
	if (NOTE_P (scan)
	    && NOTE_LINE_NUMBER (scan) == NOTE_INSN_FUNCTION_BEG)
	  break;
      if (scan == NULL_RTX)
	scan = get_insns ();
      insn = emit_insn_after (insn, scan);
      pop_topmost_sequence ();
    }

  return cfun->machine->mips16_gp_pseudo_rtx;
}