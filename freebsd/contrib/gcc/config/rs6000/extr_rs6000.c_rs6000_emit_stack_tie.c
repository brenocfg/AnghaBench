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
 int /*<<< orphan*/  BLKmode ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  STACK_POINTER_REGNUM ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_frame_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_stack_tie (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rs6000_emit_stack_tie (void)
{
  rtx mem = gen_frame_mem (BLKmode,
			   gen_rtx_REG (Pmode, STACK_POINTER_REGNUM));

  emit_insn (gen_stack_tie (mem));
}