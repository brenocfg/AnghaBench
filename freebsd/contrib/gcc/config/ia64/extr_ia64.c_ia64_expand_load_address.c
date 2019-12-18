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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ CONST ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Pmode ; 
 scalar_t__ REG ; 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ SYMBOL_REF ; 
 scalar_t__ SYMBOL_REF_FUNCTION_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_AUTO_PIC ; 
 scalar_t__ TARGET_NO_PIC ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_load_fptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_load_gprel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_load_gprel64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_HIGH (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_LO_SUM (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG_offset (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pic_offset_table_rtx ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sdata_symbolic_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ small_addr_symbolic_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
ia64_expand_load_address (rtx dest, rtx src)
{
  gcc_assert (GET_CODE (dest) == REG);

  /* ILP32 mode still loads 64-bits of data from the GOT.  This avoids
     having to pointer-extend the value afterward.  Other forms of address
     computation below are also more natural to compute as 64-bit quantities.
     If we've been given an SImode destination register, change it.  */
  if (GET_MODE (dest) != Pmode)
    dest = gen_rtx_REG_offset (dest, Pmode, REGNO (dest), 0);

  if (TARGET_NO_PIC)
    return false;
  if (small_addr_symbolic_operand (src, VOIDmode))
    return false;

  if (TARGET_AUTO_PIC)
    emit_insn (gen_load_gprel64 (dest, src));
  else if (GET_CODE (src) == SYMBOL_REF && SYMBOL_REF_FUNCTION_P (src))
    emit_insn (gen_load_fptr (dest, src));
  else if (sdata_symbolic_operand (src, VOIDmode))
    emit_insn (gen_load_gprel (dest, src));
  else
    {
      HOST_WIDE_INT addend = 0;
      rtx tmp;

      /* We did split constant offsets in ia64_expand_move, and we did try
	 to keep them split in move_operand, but we also allowed reload to
	 rematerialize arbitrary constants rather than spill the value to
	 the stack and reload it.  So we have to be prepared here to split
	 them apart again.  */
      if (GET_CODE (src) == CONST)
	{
	  HOST_WIDE_INT hi, lo;

	  hi = INTVAL (XEXP (XEXP (src, 0), 1));
	  lo = ((hi & 0x3fff) ^ 0x2000) - 0x2000;
	  hi = hi - lo;

	  if (lo != 0)
	    {
	      addend = lo;
	      src = plus_constant (XEXP (XEXP (src, 0), 0), hi);
	    }
	}

      tmp = gen_rtx_HIGH (Pmode, src);
      tmp = gen_rtx_PLUS (Pmode, tmp, pic_offset_table_rtx);
      emit_insn (gen_rtx_SET (VOIDmode, dest, tmp));

      tmp = gen_rtx_LO_SUM (Pmode, dest, src);
      emit_insn (gen_rtx_SET (VOIDmode, dest, tmp));

      if (addend)
	{
	  tmp = gen_rtx_PLUS (Pmode, dest, GEN_INT (addend));
	  emit_insn (gen_rtx_SET (VOIDmode, dest, tmp));
	}
    }

  return true;
}