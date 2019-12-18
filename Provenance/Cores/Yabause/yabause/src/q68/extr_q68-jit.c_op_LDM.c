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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_READ ; 
 scalar_t__ EA_ADDRESS_REG ; 
 int EA_INDIRECT ; 
 scalar_t__ EA_MODE (int) ; 
 scalar_t__ EA_POSTINCREMENT ; 
 scalar_t__ EA_PREDECREMENT ; 
 int EA_REG (int) ; 
 int FAULT_STATUS_IN_DATA ; 
 int FAULT_STATUS_RW_READ ; 
 unsigned int IFETCH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_CHECK_ALIGNED_EA (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  JIT_EMIT_LOADA_INC_W (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_LOAD_INC_L (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_LOAD_INC_W (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_MOVEM_WRITEBACK (int /*<<< orphan*/ ,int) ; 
 int SIZE_L ; 
 int SIZE_W ; 
 int /*<<< orphan*/  current_entry ; 
 int ea_resolve (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int op_ill (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int op_LDM(Q68State *state, uint32_t opcode)
{
    unsigned int regmask = IFETCH(state);
    int size = (opcode & 0x0040) ? SIZE_L : SIZE_W;
    if (EA_MODE(opcode) <= EA_ADDRESS_REG
     || EA_MODE(opcode) == EA_PREDECREMENT  // Not allowed for load
    ) {
        return op_ill(state, opcode);
    }

    /* Avoid modifying the register during address resolution */
    uint16_t safe_ea;
    if (EA_MODE(opcode) == EA_POSTINCREMENT) {
        safe_ea = EA_INDIRECT<<3 | EA_REG(opcode);
    } else {
        safe_ea = opcode;
    }
    int cycles = ea_resolve(state, safe_ea, SIZE_W, ACCESS_READ);
    if (cycles < 0) {
        return op_ill(state, opcode);
    }
    if (regmask != 0) {  // FIXME: does a real 68000 choke even if regmask==0?
#ifndef Q68_DISABLE_ADDRESS_ERROR
        JIT_EMIT_CHECK_ALIGNED_EA(current_entry, opcode,
                                  FAULT_STATUS_IN_DATA | FAULT_STATUS_RW_READ);
#endif
    }

    int reg;
    for (reg = 0; reg < 16; reg++, regmask >>= 1) {
        if (regmask & 1) {
            if (size == SIZE_W) {
                if (reg < 8) {
                    JIT_EMIT_LOAD_INC_W(current_entry, reg*4);
                } else {
                    JIT_EMIT_LOADA_INC_W(current_entry, reg*4);
                }
                cycles += 4;
            } else {
                JIT_EMIT_LOAD_INC_L(current_entry, reg*4);
                cycles += 8;
            }
        }
    }
    if (EA_MODE(opcode) == EA_POSTINCREMENT) {
        JIT_EMIT_MOVEM_WRITEBACK(current_entry, (8 + EA_REG(opcode)) * 4);
    }

    JIT_EMIT_ADD_CYCLES(current_entry, 8 + cycles);
    return 0;
}