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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  INSN_GET_REG0 ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_CHECK_SUPER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_MOVE_FROM_USP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_MOVE_TO_USP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current_entry ; 
 int reg0 ; 

__attribute__((used)) static int opMUSP(Q68State *state, uint32_t opcode)
{
    JIT_EMIT_CHECK_SUPER(current_entry);
    INSN_GET_REG0;
    if (opcode & 0x0008) {
        JIT_EMIT_MOVE_TO_USP(current_entry, reg0*4);
    } else {
        JIT_EMIT_MOVE_FROM_USP(current_entry, reg0*4);
    }
    JIT_EMIT_ADD_CYCLES(current_entry, 4);
    return 0;
}