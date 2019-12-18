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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  Q68State ;

/* Variables and functions */
 int FAULT_STATUS_IN_DATA ; 
 int FAULT_STATUS_RW_WRITE ; 
 int /*<<< orphan*/  IFETCH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INSN_GET_REG0 ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_CHECK_ALIGNED_SP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP1_REGISTER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP2_IMMEDIATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_MOVE_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_PUSH_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SET_REGISTER_L (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current_entry ; 
 int reg0 ; 

__attribute__((used)) static int opLINK(Q68State *state, uint32_t opcode)
{
    INSN_GET_REG0;
    int16_t disp = IFETCH(state);
#ifndef Q68_DISABLE_ADDRESS_ERROR
    JIT_EMIT_CHECK_ALIGNED_SP(current_entry, opcode,
                              FAULT_STATUS_IN_DATA | FAULT_STATUS_RW_WRITE);
#endif
    JIT_EMIT_GET_OP1_REGISTER(current_entry, (8+reg0)*4);
    JIT_EMIT_PUSH_L(current_entry);
    JIT_EMIT_GET_OP1_REGISTER(current_entry, (8+7)*4);
    JIT_EMIT_MOVE_L(current_entry);
    JIT_EMIT_SET_REGISTER_L(current_entry, (8+reg0)*4);
    JIT_EMIT_GET_OP2_IMMEDIATE(current_entry, disp);
    JIT_EMIT_ADD_L(current_entry);
    JIT_EMIT_SET_REGISTER_L(current_entry, (8+7)*4);
    JIT_EMIT_ADD_CYCLES(current_entry, 16);
    return 0;
}