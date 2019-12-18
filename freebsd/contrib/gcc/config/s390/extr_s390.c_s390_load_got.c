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
typedef  scalar_t__ rtx ;
typedef  int /*<<< orphan*/  SYMBOL_REF_FLAGS ;

/* Variables and functions */
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  SYMBOL_FLAG_LOCAL ; 
 scalar_t__ TARGET_CPU_ZARCH ; 
 int /*<<< orphan*/  UNSPEC_LTREL_BASE ; 
 int /*<<< orphan*/  UNSPEC_LTREL_OFFSET ; 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  end_sequence () ; 
 scalar_t__ force_const_mem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gen_rtvec (int,scalar_t__) ; 
 scalar_t__ gen_rtx_CONST (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_rtx_PLUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_rtx_SYMBOL_REF (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gen_rtx_UNSPEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_insns () ; 
 scalar_t__ got_symbol ; 
 int /*<<< orphan*/  pic_offset_table_rtx ; 
 int /*<<< orphan*/  start_sequence () ; 

rtx
s390_load_got (void)
{
  rtx insns;

  if (!got_symbol)
    {
      got_symbol = gen_rtx_SYMBOL_REF (Pmode, "_GLOBAL_OFFSET_TABLE_");
      SYMBOL_REF_FLAGS (got_symbol) = SYMBOL_FLAG_LOCAL;
    }

  start_sequence ();

  if (TARGET_CPU_ZARCH)
    {
      emit_move_insn (pic_offset_table_rtx, got_symbol);
    }
  else
    {
      rtx offset;

      offset = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, got_symbol),
			       UNSPEC_LTREL_OFFSET);
      offset = gen_rtx_CONST (Pmode, offset);
      offset = force_const_mem (Pmode, offset);

      emit_move_insn (pic_offset_table_rtx, offset);

      offset = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, XEXP (offset, 0)),
			       UNSPEC_LTREL_BASE);
      offset = gen_rtx_PLUS (Pmode, pic_offset_table_rtx, offset);

      emit_move_insn (pic_offset_table_rtx, offset);
    }

  insns = get_insns ();
  end_sequence ();
  return insns;
}