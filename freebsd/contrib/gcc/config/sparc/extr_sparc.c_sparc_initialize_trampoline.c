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
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  LCT_NORMAL ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_DIRECT ; 
 scalar_t__ PROCESSOR_NIAGARA ; 
 scalar_t__ PROCESSOR_ULTRASPARC ; 
 scalar_t__ PROCESSOR_ULTRASPARC3 ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  RSHIFT_EXPR ; 
 int /*<<< orphan*/  SImode ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_library_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_shift (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SYMBOL_REF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ior_optab ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  size_int (int) ; 
 scalar_t__ sparc_cpu ; 
 int trunc_int_for_mode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validize_mem (int /*<<< orphan*/ ) ; 

void
sparc_initialize_trampoline (rtx tramp, rtx fnaddr, rtx cxt)
{
  /* SPARC 32-bit trampoline:

 	sethi	%hi(fn), %g1
 	sethi	%hi(static), %g2
 	jmp	%g1+%lo(fn)
 	or	%g2, %lo(static), %g2

    SETHI i,r  = 00rr rrr1 00ii iiii iiii iiii iiii iiii
    JMPL r+i,d = 10dd ddd1 1100 0rrr rr1i iiii iiii iiii
   */

  emit_move_insn
    (gen_rtx_MEM (SImode, plus_constant (tramp, 0)),
     expand_binop (SImode, ior_optab,
		   expand_shift (RSHIFT_EXPR, SImode, fnaddr,
				 size_int (10), 0, 1),
		   GEN_INT (trunc_int_for_mode (0x03000000, SImode)),
		   NULL_RTX, 1, OPTAB_DIRECT));

  emit_move_insn
    (gen_rtx_MEM (SImode, plus_constant (tramp, 4)),
     expand_binop (SImode, ior_optab,
		   expand_shift (RSHIFT_EXPR, SImode, cxt,
				 size_int (10), 0, 1),
		   GEN_INT (trunc_int_for_mode (0x05000000, SImode)),
		   NULL_RTX, 1, OPTAB_DIRECT));

  emit_move_insn
    (gen_rtx_MEM (SImode, plus_constant (tramp, 8)),
     expand_binop (SImode, ior_optab,
		   expand_and (SImode, fnaddr, GEN_INT (0x3ff), NULL_RTX),
		   GEN_INT (trunc_int_for_mode (0x81c06000, SImode)),
		   NULL_RTX, 1, OPTAB_DIRECT));

  emit_move_insn
    (gen_rtx_MEM (SImode, plus_constant (tramp, 12)),
     expand_binop (SImode, ior_optab,
		   expand_and (SImode, cxt, GEN_INT (0x3ff), NULL_RTX),
		   GEN_INT (trunc_int_for_mode (0x8410a000, SImode)),
		   NULL_RTX, 1, OPTAB_DIRECT));

  /* On UltraSPARC a flush flushes an entire cache line.  The trampoline is
     aligned on a 16 byte boundary so one flush clears it all.  */
  emit_insn (gen_flush (validize_mem (gen_rtx_MEM (SImode, tramp))));
  if (sparc_cpu != PROCESSOR_ULTRASPARC
      && sparc_cpu != PROCESSOR_ULTRASPARC3
      && sparc_cpu != PROCESSOR_NIAGARA)
    emit_insn (gen_flush (validize_mem (gen_rtx_MEM (SImode,
						     plus_constant (tramp, 8)))));

  /* Call __enable_execute_stack after writing onto the stack to make sure
     the stack address is accessible.  */
#ifdef ENABLE_EXECUTE_STACK
  emit_library_call (gen_rtx_SYMBOL_REF (Pmode, "__enable_execute_stack"),
                     LCT_NORMAL, VOIDmode, 1, tramp, Pmode);
#endif

}