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
 scalar_t__ Pmode ; 
 scalar_t__ SImode ; 
 int /*<<< orphan*/  SYMBOL_GOTOFF_CALL ; 
 scalar_t__ TARGET_EXPLICIT_RELOCS ; 
 scalar_t__ TARGET_NEWABI ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_load_calldi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_load_callsi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ global_got_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_unspec_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_unspec_offset_high (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pic_offset_table_rtx ; 

__attribute__((used)) static void
mips_load_call_address (rtx dest, rtx addr, int sibcall_p)
{
  /* If we're generating PIC, and this call is to a global function,
     try to allow its address to be resolved lazily.  This isn't
     possible for NewABI sibcalls since the value of $gp on entry
     to the stub would be our caller's gp, not ours.  */
  if (TARGET_EXPLICIT_RELOCS
      && !(sibcall_p && TARGET_NEWABI)
      && global_got_operand (addr, VOIDmode))
    {
      rtx high, lo_sum_symbol;

      high = mips_unspec_offset_high (dest, pic_offset_table_rtx,
				      addr, SYMBOL_GOTOFF_CALL);
      lo_sum_symbol = mips_unspec_address (addr, SYMBOL_GOTOFF_CALL);
      if (Pmode == SImode)
	emit_insn (gen_load_callsi (dest, high, lo_sum_symbol));
      else
	emit_insn (gen_load_calldi (dest, high, lo_sum_symbol));
    }
  else
    emit_move_insn (dest, addr);
}