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
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ ALTIVEC_VECTOR_MODE (int) ; 
 int DFmode ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int Pmode ; 
 int /*<<< orphan*/  SPE_CONST_OFFSET_OK (int) ; 
 scalar_t__ SPE_VECTOR_MODE (int) ; 
 scalar_t__ TARGET_ALTIVEC_ABI ; 
 scalar_t__ TARGET_E500_DOUBLE ; 
 scalar_t__ TARGET_SPE_ABI ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_frame_mem (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int,unsigned int) ; 
 int /*<<< orphan*/  rs6000_frame_related (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
emit_frame_save (rtx frame_reg, rtx frame_ptr, enum machine_mode mode,
		 unsigned int regno, int offset, HOST_WIDE_INT total_size)
{
  rtx reg, offset_rtx, insn, mem, addr, int_rtx;
  rtx replacea, replaceb;

  int_rtx = GEN_INT (offset);

  /* Some cases that need register indexed addressing.  */
  if ((TARGET_ALTIVEC_ABI && ALTIVEC_VECTOR_MODE (mode))
      || (TARGET_E500_DOUBLE && mode == DFmode)
      || (TARGET_SPE_ABI
	  && SPE_VECTOR_MODE (mode)
	  && !SPE_CONST_OFFSET_OK (offset)))
    {
      /* Whomever calls us must make sure r11 is available in the
	 flow path of instructions in the prologue.  */
      offset_rtx = gen_rtx_REG (Pmode, 11);
      emit_move_insn (offset_rtx, int_rtx);

      replacea = offset_rtx;
      replaceb = int_rtx;
    }
  else
    {
      offset_rtx = int_rtx;
      replacea = NULL_RTX;
      replaceb = NULL_RTX;
    }

  reg = gen_rtx_REG (mode, regno);
  addr = gen_rtx_PLUS (Pmode, frame_reg, offset_rtx);
  mem = gen_frame_mem (mode, addr);

  insn = emit_move_insn (mem, reg);

  rs6000_frame_related (insn, frame_ptr, total_size, replacea, replaceb);
}