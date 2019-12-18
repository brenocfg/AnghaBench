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
 int /*<<< orphan*/  GEN_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCT_NORMAL ; 
 scalar_t__ PROCESSOR_NIAGARA ; 
 scalar_t__ PROCESSOR_ULTRASPARC ; 
 scalar_t__ PROCESSOR_ULTRASPARC3 ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  SImode ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_library_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_flushdi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SYMBOL_REF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sparc_cpu ; 
 int /*<<< orphan*/  trunc_int_for_mode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validize_mem (int /*<<< orphan*/ ) ; 

void
sparc64_initialize_trampoline (rtx tramp, rtx fnaddr, rtx cxt)
{
  /* SPARC 64-bit trampoline:

	rd	%pc, %g1
	ldx	[%g1+24], %g5
	jmp	%g5
	ldx	[%g1+16], %g5
	+16 bytes data
   */

  emit_move_insn (gen_rtx_MEM (SImode, tramp),
		  GEN_INT (trunc_int_for_mode (0x83414000, SImode)));
  emit_move_insn (gen_rtx_MEM (SImode, plus_constant (tramp, 4)),
		  GEN_INT (trunc_int_for_mode (0xca586018, SImode)));
  emit_move_insn (gen_rtx_MEM (SImode, plus_constant (tramp, 8)),
		  GEN_INT (trunc_int_for_mode (0x81c14000, SImode)));
  emit_move_insn (gen_rtx_MEM (SImode, plus_constant (tramp, 12)),
		  GEN_INT (trunc_int_for_mode (0xca586010, SImode)));
  emit_move_insn (gen_rtx_MEM (DImode, plus_constant (tramp, 16)), cxt);
  emit_move_insn (gen_rtx_MEM (DImode, plus_constant (tramp, 24)), fnaddr);
  emit_insn (gen_flushdi (validize_mem (gen_rtx_MEM (DImode, tramp))));

  if (sparc_cpu != PROCESSOR_ULTRASPARC
      && sparc_cpu != PROCESSOR_ULTRASPARC3
      && sparc_cpu != PROCESSOR_NIAGARA)
    emit_insn (gen_flushdi (validize_mem (gen_rtx_MEM (DImode, plus_constant (tramp, 8)))));

  /* Call __enable_execute_stack after writing onto the stack to make sure
     the stack address is accessible.  */
#ifdef ENABLE_EXECUTE_STACK
  emit_library_call (gen_rtx_SYMBOL_REF (Pmode, "__enable_execute_stack"),
                     LCT_NORMAL, VOIDmode, 1, tramp, Pmode);
#endif
}