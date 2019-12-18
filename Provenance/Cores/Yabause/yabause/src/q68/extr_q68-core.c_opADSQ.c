#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int SR; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 scalar_t__ EA_ADDRESS_REG ; 
 scalar_t__ EA_INDIRECT ; 
 scalar_t__ EA_MODE (int) ; 
 int /*<<< orphan*/  INSN_CLEAR_XCC () ; 
 int /*<<< orphan*/  INSN_GET_COUNT ; 
 int /*<<< orphan*/  INSN_GET_SIZE ; 
 int /*<<< orphan*/  INSN_SETNZ_SHIFT (int) ; 
 int SIZE_L ; 
 int SIZE_TO_BYTES (int) ; 
 int SR_C ; 
 int SR_V ; 
 int SR_X ; 
 int count ; 
 int ea_get (TYPE_1__*,int,int,int,int*) ; 
 int /*<<< orphan*/  ea_set (TYPE_1__*,int,int,int) ; 
 int size ; 

__attribute__((used)) static int opADSQ(Q68State *state, uint32_t opcode)
{
    const int is_sub = opcode & 0x0100;
    INSN_GET_COUNT;
    INSN_GET_SIZE;
    if (EA_MODE(opcode) == EA_ADDRESS_REG && size == 1) {
        size = 2;  // ADDQ.W #imm,An is equivalent to ADDQ.L #imm,An
    }
    const int bytes = SIZE_TO_BYTES(size);
    const int shift = bytes*8 - 1;
    const uint32_t valuemask = ~(~1 << shift);
    int cycles;
    uint32_t data = ea_get(state, opcode, size, 1, &cycles);
    if (cycles < 0) {
        return 0;
    }

    uint32_t result;
    if (is_sub) {
        result = data - count;
    } else {
        result = data + count;
    }
    result &= valuemask;
    if (EA_MODE(opcode) != EA_ADDRESS_REG) {
        INSN_CLEAR_XCC();
        INSN_SETNZ_SHIFT(result);
        if ((is_sub ? ~result & data : result & ~data) >> shift) {
            state->SR |= SR_V;
        }
        if ((is_sub ? result & ~data : ~result & data) >> shift) {
            state->SR |= SR_X | SR_C;
        }
    }
    
    ea_set(state, opcode, size, result);
    return (size==SIZE_L || EA_MODE(opcode) == EA_ADDRESS_REG ? 8 : 4)
           + (EA_MODE(opcode) >= EA_INDIRECT ? 4 : 0) + cycles;
}