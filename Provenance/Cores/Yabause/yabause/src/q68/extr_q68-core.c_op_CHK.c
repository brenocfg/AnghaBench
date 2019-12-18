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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_5__ {void* exception; int /*<<< orphan*/  SR; scalar_t__* D; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 scalar_t__ EA_ADDRESS_REG ; 
 scalar_t__ EA_MODE (int /*<<< orphan*/ ) ; 
 void* EX_CHK ; 
 int /*<<< orphan*/  INSN_GET_REG ; 
 int SIZE_W ; 
 int /*<<< orphan*/  SR_N ; 
 scalar_t__ ea_get (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int op_ill (TYPE_1__*,int /*<<< orphan*/ ) ; 
 size_t reg ; 

__attribute__((used)) static int op_CHK(Q68State *state, uint32_t opcode)
{
    INSN_GET_REG;
    int size = SIZE_W;  // Bit 7 == 0 indicates long mode on the 68020

    int cycles;
    int32_t upper;  // Yes, it's signed
    if (EA_MODE(opcode) == EA_ADDRESS_REG) {
        return op_ill(state, opcode);
    }
    upper = ea_get(state, opcode, size, 0, &cycles);
    if (cycles < 0) {
        return 0;
    }
    if (size == SIZE_W) {
        upper = (int32_t)(int16_t)upper;
    }

    int32_t value;
    if (size == SIZE_W) {
        value = (int32_t)(int16_t)state->D[reg];
    } else {
        value = (int32_t)state->D[reg];
    }
    if (value < 0) {
        state->SR |= SR_N;
        state->exception = EX_CHK;
        return cycles;
    } else if (value > upper) {
        state->SR &= ~SR_N;
        state->exception = EX_CHK;
        return cycles;
    }

    return 10 + cycles;
}