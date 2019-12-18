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

/* Variables and functions */
 int /*<<< orphan*/  DImode ; 
 int /*<<< orphan*/  HImode ; 
 int /*<<< orphan*/  LCT_NORMAL ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_DIRECT ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  QImode ; 
 int /*<<< orphan*/  SImode ; 
 int /*<<< orphan*/  TARGET_64BIT ; 
 int TRAMPOLINE_SIZE ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  copy_to_mode_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_library_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_int_mode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_lowpart (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SYMBOL_REF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sub_optab ; 
 scalar_t__ x86_64_zext_immediate_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
x86_initialize_trampoline (rtx tramp, rtx fnaddr, rtx cxt)
{
  if (!TARGET_64BIT)
    {
      /* Compute offset from the end of the jmp to the target function.  */
      rtx disp = expand_binop (SImode, sub_optab, fnaddr,
			       plus_constant (tramp, 10),
			       NULL_RTX, 1, OPTAB_DIRECT);
      emit_move_insn (gen_rtx_MEM (QImode, tramp),
		      gen_int_mode (0xb9, QImode));
      emit_move_insn (gen_rtx_MEM (SImode, plus_constant (tramp, 1)), cxt);
      emit_move_insn (gen_rtx_MEM (QImode, plus_constant (tramp, 5)),
		      gen_int_mode (0xe9, QImode));
      emit_move_insn (gen_rtx_MEM (SImode, plus_constant (tramp, 6)), disp);
    }
  else
    {
      int offset = 0;
      /* Try to load address using shorter movl instead of movabs.
         We may want to support movq for kernel mode, but kernel does not use
         trampolines at the moment.  */
      if (x86_64_zext_immediate_operand (fnaddr, VOIDmode))
	{
	  fnaddr = copy_to_mode_reg (DImode, fnaddr);
	  emit_move_insn (gen_rtx_MEM (HImode, plus_constant (tramp, offset)),
			  gen_int_mode (0xbb41, HImode));
	  emit_move_insn (gen_rtx_MEM (SImode, plus_constant (tramp, offset + 2)),
			  gen_lowpart (SImode, fnaddr));
	  offset += 6;
	}
      else
	{
	  emit_move_insn (gen_rtx_MEM (HImode, plus_constant (tramp, offset)),
			  gen_int_mode (0xbb49, HImode));
	  emit_move_insn (gen_rtx_MEM (DImode, plus_constant (tramp, offset + 2)),
			  fnaddr);
	  offset += 10;
	}
      /* Load static chain using movabs to r10.  */
      emit_move_insn (gen_rtx_MEM (HImode, plus_constant (tramp, offset)),
		      gen_int_mode (0xba49, HImode));
      emit_move_insn (gen_rtx_MEM (DImode, plus_constant (tramp, offset + 2)),
		      cxt);
      offset += 10;
      /* Jump to the r11 */
      emit_move_insn (gen_rtx_MEM (HImode, plus_constant (tramp, offset)),
		      gen_int_mode (0xff49, HImode));
      emit_move_insn (gen_rtx_MEM (QImode, plus_constant (tramp, offset+2)),
		      gen_int_mode (0xe3, QImode));
      offset += 3;
      gcc_assert (offset <= TRAMPOLINE_SIZE);
    }

#ifdef ENABLE_EXECUTE_STACK
  emit_library_call (gen_rtx_SYMBOL_REF (Pmode, "__enable_execute_stack"),
		     LCT_NORMAL, VOIDmode, 1, tramp, Pmode);
#endif
}