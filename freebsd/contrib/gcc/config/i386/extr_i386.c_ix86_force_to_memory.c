#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
#define  DImode 130 
 int /*<<< orphan*/  GEN_INT (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
#define  HImode 129 
 int const Pmode ; 
 int /*<<< orphan*/  RED_ZONE_SIZE ; 
#define  SImode 128 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ TARGET_RED_ZONE ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_lowpart (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PRE_DEC (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reload_completed ; 
 int /*<<< orphan*/  split_di (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 

rtx
ix86_force_to_memory (enum machine_mode mode, rtx operand)
{
  rtx result;

  gcc_assert (reload_completed);
  if (TARGET_RED_ZONE)
    {
      result = gen_rtx_MEM (mode,
			    gen_rtx_PLUS (Pmode,
					  stack_pointer_rtx,
					  GEN_INT (-RED_ZONE_SIZE)));
      emit_move_insn (result, operand);
    }
  else if (!TARGET_RED_ZONE && TARGET_64BIT)
    {
      switch (mode)
	{
	case HImode:
	case SImode:
	  operand = gen_lowpart (DImode, operand);
	  /* FALLTHRU */
	case DImode:
	  emit_insn (
		      gen_rtx_SET (VOIDmode,
				   gen_rtx_MEM (DImode,
						gen_rtx_PRE_DEC (DImode,
							stack_pointer_rtx)),
				   operand));
	  break;
	default:
	  gcc_unreachable ();
	}
      result = gen_rtx_MEM (mode, stack_pointer_rtx);
    }
  else
    {
      switch (mode)
	{
	case DImode:
	  {
	    rtx operands[2];
	    split_di (&operand, 1, operands, operands + 1);
	    emit_insn (
			gen_rtx_SET (VOIDmode,
				     gen_rtx_MEM (SImode,
						  gen_rtx_PRE_DEC (Pmode,
							stack_pointer_rtx)),
				     operands[1]));
	    emit_insn (
			gen_rtx_SET (VOIDmode,
				     gen_rtx_MEM (SImode,
						  gen_rtx_PRE_DEC (Pmode,
							stack_pointer_rtx)),
				     operands[0]));
	  }
	  break;
	case HImode:
	  /* Store HImodes as SImodes.  */
	  operand = gen_lowpart (SImode, operand);
	  /* FALLTHRU */
	case SImode:
	  emit_insn (
		      gen_rtx_SET (VOIDmode,
				   gen_rtx_MEM (GET_MODE (operand),
						gen_rtx_PRE_DEC (SImode,
							stack_pointer_rtx)),
				   operand));
	  break;
	default:
	  gcc_unreachable ();
	}
      result = gen_rtx_MEM (mode, stack_pointer_rtx);
    }
  return result;
}