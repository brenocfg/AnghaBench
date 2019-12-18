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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int DImode ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ TARGET_64BIT ; 
 int /*<<< orphan*/  TARGET_RED_ZONE ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 

void
ix86_free_from_memory (enum machine_mode mode)
{
  if (!TARGET_RED_ZONE)
    {
      int size;

      if (mode == DImode || TARGET_64BIT)
	size = 8;
      else
	size = 4;
      /* Use LEA to deallocate stack space.  In peephole2 it will be converted
         to pop or add instruction if registers are available.  */
      emit_insn (gen_rtx_SET (VOIDmode, stack_pointer_rtx,
			      gen_rtx_PLUS (Pmode, stack_pointer_rtx,
					    GEN_INT (size))));
    }
}