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
typedef  int /*<<< orphan*/  (* mips_save_restore_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  gen_frame_mem (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int,int) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 

__attribute__((used)) static void
mips_save_restore_reg (enum machine_mode mode, int regno,
		       HOST_WIDE_INT offset, mips_save_restore_fn fn)
{
  rtx mem;

  mem = gen_frame_mem (mode, plus_constant (stack_pointer_rtx, offset));

  fn (gen_rtx_REG (mode, regno), mem);
}