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
 int /*<<< orphan*/  HImode ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QImode ; 
 int /*<<< orphan*/  SImode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_to_mode_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_movhi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_movmem12b (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_movmem8b (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_movqi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_movsi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 

void
thumb_expand_movmemqi (rtx *operands)
{
  rtx out = copy_to_mode_reg (SImode, XEXP (operands[0], 0));
  rtx in  = copy_to_mode_reg (SImode, XEXP (operands[1], 0));
  HOST_WIDE_INT len = INTVAL (operands[2]);
  HOST_WIDE_INT offset = 0;

  while (len >= 12)
    {
      emit_insn (gen_movmem12b (out, in, out, in));
      len -= 12;
    }

  if (len >= 8)
    {
      emit_insn (gen_movmem8b (out, in, out, in));
      len -= 8;
    }

  if (len >= 4)
    {
      rtx reg = gen_reg_rtx (SImode);
      emit_insn (gen_movsi (reg, gen_rtx_MEM (SImode, in)));
      emit_insn (gen_movsi (gen_rtx_MEM (SImode, out), reg));
      len -= 4;
      offset += 4;
    }

  if (len >= 2)
    {
      rtx reg = gen_reg_rtx (HImode);
      emit_insn (gen_movhi (reg, gen_rtx_MEM (HImode,
					      plus_constant (in, offset))));
      emit_insn (gen_movhi (gen_rtx_MEM (HImode, plus_constant (out, offset)),
			    reg));
      len -= 2;
      offset += 2;
    }

  if (len)
    {
      rtx reg = gen_reg_rtx (QImode);
      emit_insn (gen_movqi (reg, gen_rtx_MEM (QImode,
					      plus_constant (in, offset))));
      emit_insn (gen_movqi (gen_rtx_MEM (QImode, plus_constant (out, offset)),
			    reg));
    }
}