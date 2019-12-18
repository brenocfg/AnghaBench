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
typedef  int RTX_FRAME_RELATED_P ;

/* Variables and functions */
 unsigned int FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ ix86_save_reg (unsigned int,int) ; 

__attribute__((used)) static void
ix86_emit_save_regs (void)
{
  unsigned int regno;
  rtx insn;

  for (regno = FIRST_PSEUDO_REGISTER; regno-- > 0; )
    if (ix86_save_reg (regno, true))
      {
	insn = emit_insn (gen_push (gen_rtx_REG (Pmode, regno)));
	RTX_FRAME_RELATED_P (insn) = 1;
      }
}