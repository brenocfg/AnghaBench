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
typedef  int /*<<< orphan*/  Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_READ ; 
 scalar_t__ EA_ADDRESS_REG ; 
 scalar_t__ EA_DATA_REG ; 
 scalar_t__ EA_MISC ; 
 scalar_t__ EA_MISC_IMMEDIATE ; 
 scalar_t__ EA_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ EA_POSTINCREMENT ; 
 scalar_t__ EA_PREDECREMENT ; 
 scalar_t__ EA_REG (int /*<<< orphan*/ ) ; 
 int FAULT_STATUS_IN_DATA ; 
 int FAULT_STATUS_RW_WRITE ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_CHECK_ALIGNED_SP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_PEA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIZE_W ; 
 int /*<<< orphan*/  current_entry ; 
 int ea_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int opSWAP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int op_ill (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int op_PEA(Q68State *state, uint32_t opcode)
{
    /* SWAP is coded as PEA Dn */
    if (EA_MODE(opcode) == EA_DATA_REG) {
        return opSWAP(state, opcode);
    }

    if (EA_MODE(opcode) == EA_DATA_REG
     || EA_MODE(opcode) == EA_ADDRESS_REG
     || EA_MODE(opcode) == EA_POSTINCREMENT
     || EA_MODE(opcode) == EA_PREDECREMENT
     || (EA_MODE(opcode) == EA_MISC && EA_REG(opcode) == EA_MISC_IMMEDIATE)
    ) {
        return op_ill(state, opcode);
    }

    int cycles = ea_resolve(state, opcode, SIZE_W, ACCESS_READ);
    if (cycles < 0) {
        return op_ill(state, opcode);
    }
    if (cycles % 4 == 2) {  // d(An,ix) and d(PC,ix) take 2 extra cycles
        cycles += 2;
    }

#ifndef Q68_DISABLE_ADDRESS_ERROR
    JIT_EMIT_CHECK_ALIGNED_SP(current_entry, opcode,
                              FAULT_STATUS_IN_DATA | FAULT_STATUS_RW_WRITE);
#endif
    JIT_EMIT_PEA(current_entry);
    JIT_EMIT_ADD_CYCLES(current_entry, 8 + cycles);
    return 0;
}