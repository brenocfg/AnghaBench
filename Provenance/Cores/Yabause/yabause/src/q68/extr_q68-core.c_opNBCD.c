#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int SR; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 scalar_t__ EA_ADDRESS_REG ; 
 scalar_t__ EA_DATA_REG ; 
 scalar_t__ EA_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIZE_B ; 
 int SR_C ; 
 int SR_X ; 
 int SR_X_SHIFT ; 
 int SR_Z ; 
 int ea_get (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  ea_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int op_ill (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opNBCD(Q68State *state, uint32_t opcode)
{
    if (EA_MODE(opcode) == EA_ADDRESS_REG) {  // Address registers not allowed
        return op_ill(state, opcode);
    }

    int cycles;
    int value = ea_get(state, opcode, SIZE_B, 1, &cycles);
    if (cycles < 0) {
        return 0;
    }

    int result;
    int X = (state->SR >> SR_X_SHIFT) & 1;
    state->SR &= ~(SR_X | SR_C);  // Z is never set, only cleared
    /* Slightly convoluted to match what a real 68000 does (see SBCD) */
    int res_low = 0 - (value & 0x0F) - X;
    int borrow = 0;
    if (res_low < 0) {
        res_low += 10;
        borrow = 1<<4;
    }
    int res_high = 0 - (value & 0xF0) - borrow;
    if (res_high < 0) {
        res_high += 10<<4;
        state->SR |= SR_X | SR_C;
    }
    result = res_high + res_low;
    if (result < 0) {
        state->SR |= SR_X | SR_C;
    }
    result &= 0xFF;
    if (result != 0) {
        state->SR &= ~SR_Z;
    }

    ea_set(state, opcode, SIZE_B, result);
    return (EA_MODE(opcode) == EA_DATA_REG ? 6 : 8) + cycles;
}