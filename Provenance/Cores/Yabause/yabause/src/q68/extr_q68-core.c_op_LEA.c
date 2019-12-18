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
struct TYPE_5__ {int /*<<< orphan*/  ea_addr; int /*<<< orphan*/ * A; } ;
typedef  TYPE_1__ Q68State ;

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
 int /*<<< orphan*/  INSN_GET_REG ; 
 int /*<<< orphan*/  SIZE_W ; 
 int ea_resolve (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int op_ill (TYPE_1__*,int /*<<< orphan*/ ) ; 
 size_t reg ; 

__attribute__((used)) static int op_LEA(Q68State *state, uint32_t opcode)
{
    INSN_GET_REG;

    /* Register, predecrement, postincrement, immediate modes are illegal */
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
    state->A[reg] = state->ea_addr;
    return cycles;
}