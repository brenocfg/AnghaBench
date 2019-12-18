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
 int /*<<< orphan*/  DImode ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  TARGET_POWERPC64 ; 
 scalar_t__ WORDS_BIG_ENDIAN ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_ASHIFT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_IOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  operand_subword_force (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
rs6000_emit_set_long_const (rtx dest, HOST_WIDE_INT c1, HOST_WIDE_INT c2)
{
  if (!TARGET_POWERPC64)
    {
      rtx operand1, operand2;

      operand1 = operand_subword_force (dest, WORDS_BIG_ENDIAN == 0,
					DImode);
      operand2 = operand_subword_force (dest, WORDS_BIG_ENDIAN != 0,
					DImode);
      emit_move_insn (operand1, GEN_INT (c1));
      emit_move_insn (operand2, GEN_INT (c2));
    }
  else
    {
      HOST_WIDE_INT ud1, ud2, ud3, ud4;

      ud1 = c1 & 0xffff;
      ud2 = (c1 & 0xffff0000) >> 16;
#if HOST_BITS_PER_WIDE_INT >= 64
      c2 = c1 >> 32;
#endif
      ud3 = c2 & 0xffff;
      ud4 = (c2 & 0xffff0000) >> 16;

      if ((ud4 == 0xffff && ud3 == 0xffff && ud2 == 0xffff && (ud1 & 0x8000))
	  || (ud4 == 0 && ud3 == 0 && ud2 == 0 && ! (ud1 & 0x8000)))
	{
	  if (ud1 & 0x8000)
	    emit_move_insn (dest, GEN_INT (((ud1 ^ 0x8000) -  0x8000)));
	  else
	    emit_move_insn (dest, GEN_INT (ud1));
	}

      else if ((ud4 == 0xffff && ud3 == 0xffff && (ud2 & 0x8000))
	       || (ud4 == 0 && ud3 == 0 && ! (ud2 & 0x8000)))
	{
	  if (ud2 & 0x8000)
	    emit_move_insn (dest, GEN_INT (((ud2 << 16) ^ 0x80000000)
					   - 0x80000000));
	  else
	    emit_move_insn (dest, GEN_INT (ud2 << 16));
	  if (ud1 != 0)
	    emit_move_insn (dest, gen_rtx_IOR (DImode, dest, GEN_INT (ud1)));
	}
      else if ((ud4 == 0xffff && (ud3 & 0x8000))
	       || (ud4 == 0 && ! (ud3 & 0x8000)))
	{
	  if (ud3 & 0x8000)
	    emit_move_insn (dest, GEN_INT (((ud3 << 16) ^ 0x80000000)
					   - 0x80000000));
	  else
	    emit_move_insn (dest, GEN_INT (ud3 << 16));

	  if (ud2 != 0)
	    emit_move_insn (dest, gen_rtx_IOR (DImode, dest, GEN_INT (ud2)));
	  emit_move_insn (dest, gen_rtx_ASHIFT (DImode, dest, GEN_INT (16)));
	  if (ud1 != 0)
	    emit_move_insn (dest, gen_rtx_IOR (DImode, dest, GEN_INT (ud1)));
	}
      else
	{
	  if (ud4 & 0x8000)
	    emit_move_insn (dest, GEN_INT (((ud4 << 16) ^ 0x80000000)
					   - 0x80000000));
	  else
	    emit_move_insn (dest, GEN_INT (ud4 << 16));

	  if (ud3 != 0)
	    emit_move_insn (dest, gen_rtx_IOR (DImode, dest, GEN_INT (ud3)));

	  emit_move_insn (dest, gen_rtx_ASHIFT (DImode, dest, GEN_INT (32)));
	  if (ud2 != 0)
	    emit_move_insn (dest, gen_rtx_IOR (DImode, dest,
					       GEN_INT (ud2 << 16)));
	  if (ud1 != 0)
	    emit_move_insn (dest, gen_rtx_IOR (DImode, dest, GEN_INT (ud1)));
	}
    }
  return dest;
}