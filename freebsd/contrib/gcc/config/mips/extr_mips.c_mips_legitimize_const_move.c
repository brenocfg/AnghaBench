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
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ SMALL_OPERAND (scalar_t__) ; 
 int /*<<< orphan*/  TARGET_MIPS16 ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_const_mem (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_add_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mips_force_temporary (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_legitimize_tls_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_move_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_split_const (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  mips_split_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mips_tls_operand_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  no_new_pseudos ; 
 int /*<<< orphan*/  replace_equiv_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ splittable_const_int_operand (int /*<<< orphan*/ ,int) ; 
 scalar_t__ splittable_symbolic_operand (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mips_legitimize_const_move (enum machine_mode mode, rtx dest, rtx src)
{
  rtx base;
  HOST_WIDE_INT offset;

  /* Split moves of big integers into smaller pieces.  */
  if (splittable_const_int_operand (src, mode))
    {
      mips_move_integer (dest, dest, INTVAL (src));
      return;
    }

  /* Split moves of symbolic constants into high/low pairs.  */
  if (splittable_symbolic_operand (src, mode))
    {
      emit_insn (gen_rtx_SET (VOIDmode, dest, mips_split_symbol (dest, src)));
      return;
    }

  if (mips_tls_operand_p (src))
    {
      emit_move_insn (dest, mips_legitimize_tls_address (src));
      return;
    }

  /* If we have (const (plus symbol offset)), load the symbol first
     and then add in the offset.  This is usually better than forcing
     the constant into memory, at least in non-mips16 code.  */
  mips_split_const (src, &base, &offset);
  if (!TARGET_MIPS16
      && offset != 0
      && (!no_new_pseudos || SMALL_OPERAND (offset)))
    {
      base = mips_force_temporary (dest, base);
      emit_move_insn (dest, mips_add_offset (0, base, offset));
      return;
    }

  src = force_const_mem (mode, src);

  /* When using explicit relocs, constant pool references are sometimes
     not legitimate addresses.  */
  if (!memory_operand (src, VOIDmode))
    src = replace_equiv_address (src, mips_split_symbol (dest, XEXP (src, 0)));
  emit_move_insn (dest, src);
}