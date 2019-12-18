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
typedef  int int8_t ;
typedef  int /*<<< orphan*/  Q68State ;

/* Variables and functions */
 scalar_t__ EA_ADDRESS_REG ; 
 scalar_t__ EA_DATA_REG ; 
 scalar_t__ EA_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_CLEAR_CC () ; 
 int /*<<< orphan*/  INSN_SETNZ (int) ; 
 int /*<<< orphan*/  SIZE_B ; 
 int ea_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  ea_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int op_ill (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int op_TAS(Q68State *state, uint32_t opcode)
{
    if (EA_MODE(opcode) == EA_ADDRESS_REG) {  // Address registers not allowed
        return op_ill(state, opcode);
    }

    int cycles;
    int8_t value = ea_get(state, opcode, SIZE_B, 1, &cycles);
    if (cycles < 0) {
        /* Note that the ILLEGAL instruction is coded as TAS #imm, so it
         * will be rejected as unwriteable by ea_get() */
        return 0;
    }

    INSN_CLEAR_CC();
    INSN_SETNZ(value);
    ea_set(state, opcode, SIZE_B, value | 0x80);
    return (EA_MODE(opcode) == EA_DATA_REG ? 4 : 10) + cycles;
}