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
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  SORR_RESTORE ; 
 int actual_fsize ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_save_or_restore_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_stack_pointer_dec (int /*<<< orphan*/ ) ; 
 scalar_t__ num_gfregs ; 
 scalar_t__ sparc_leaf_function_p ; 

void
sparc_expand_epilogue (void)
{
  if (num_gfregs)
    emit_save_or_restore_regs (SORR_RESTORE);

  if (actual_fsize == 0)
    /* do nothing.  */ ;
  else if (sparc_leaf_function_p)
    {
      if (actual_fsize <= 4096)
	emit_insn (gen_stack_pointer_dec (GEN_INT (- actual_fsize)));
      else if (actual_fsize <= 8192)
	{
	  emit_insn (gen_stack_pointer_dec (GEN_INT (-4096)));
	  emit_insn (gen_stack_pointer_dec (GEN_INT (4096 - actual_fsize)));
	}
      else
	{
	  rtx reg = gen_rtx_REG (Pmode, 1);
	  emit_move_insn (reg, GEN_INT (-actual_fsize));
	  emit_insn (gen_stack_pointer_dec (reg));
	}
    }
}