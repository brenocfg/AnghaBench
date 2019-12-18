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
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ TARGET_64BIT ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 

void
s390_initialize_trampoline (rtx addr, rtx fnaddr, rtx cxt)
{
  emit_move_insn (gen_rtx_MEM (Pmode,
		   memory_address (Pmode,
		   plus_constant (addr, (TARGET_64BIT ? 16 : 8)))), cxt);
  emit_move_insn (gen_rtx_MEM (Pmode,
		   memory_address (Pmode,
		   plus_constant (addr, (TARGET_64BIT ? 24 : 12)))), fnaddr);
}