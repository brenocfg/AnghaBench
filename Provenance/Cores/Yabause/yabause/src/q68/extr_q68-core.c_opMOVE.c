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
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_WRITE ; 
 scalar_t__ EA_ADDRESS_REG ; 
 scalar_t__ EA_MODE (int const) ; 
 int /*<<< orphan*/  INSN_CLEAR_CC () ; 
 int /*<<< orphan*/  INSN_SETNZ (int /*<<< orphan*/ ) ; 
 int const SIZE_B ; 
 int const SIZE_L ; 
 int const SIZE_W ; 
 int ea_get (int /*<<< orphan*/ *,int,int const,int /*<<< orphan*/ ,int*) ; 
 int ea_resolve (int /*<<< orphan*/ *,int const,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ea_set (int /*<<< orphan*/ *,int const,int const,int const) ; 
 int op_ill (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int opMOVE(Q68State *state, uint32_t opcode)
{
    const int size = (opcode>>12==1 ? SIZE_B : opcode>>12==2 ? SIZE_L : SIZE_W);

    int cycles_src;
    const uint32_t data = ea_get(state, opcode, size, 0, &cycles_src);
    if (cycles_src < 0) {
        return 0;
    }

    /* Rearrange the opcode bits so we can pass the destination EA to
     * ea_resolve() */
    const uint32_t dummy_opcode = (opcode>>9 & 7) | (opcode>>3 & 0x38);
    int cycles_dest;
    if (EA_MODE(dummy_opcode) <= EA_ADDRESS_REG) {
        cycles_dest = 0;
    } else {
        cycles_dest = ea_resolve(state, dummy_opcode, size, ACCESS_WRITE);
        if (cycles_dest < 0) {
            return op_ill(state, opcode);
        }
    }

    /* Update condition codes if the target is not an address register */
    if (EA_MODE(dummy_opcode) != EA_ADDRESS_REG) {
        INSN_CLEAR_CC();
        INSN_SETNZ(size==SIZE_B ? (int8_t)data :
                   size==SIZE_W ? (int16_t)data : (int32_t)data);
    }

    /* Update the destination EA and return */
    ea_set(state, dummy_opcode, size, data);
    return 4 + cycles_src + cycles_dest;
}