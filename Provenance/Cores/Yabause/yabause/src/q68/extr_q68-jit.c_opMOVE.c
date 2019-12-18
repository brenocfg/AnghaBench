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
 int /*<<< orphan*/  ACCESS_WRITE ; 
 scalar_t__ EA_ADDRESS_REG ; 
 scalar_t__ EA_MODE (int const) ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_EXT_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_MOVE_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_MOVE_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_MOVE_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_LOGIC_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_LOGIC_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_LOGIC_W (int /*<<< orphan*/ ) ; 
 int const SIZE_B ; 
 int const SIZE_L ; 
 int const SIZE_W ; 
 int cc_needed (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  current_entry ; 
 int /*<<< orphan*/  ea_get (int /*<<< orphan*/ *,int,int const,int /*<<< orphan*/ ,int*,int) ; 
 int ea_resolve (int /*<<< orphan*/ *,int const,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ea_set (int /*<<< orphan*/ *,int const,int const) ; 
 int op_ill (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int opMOVE(Q68State *state, uint32_t opcode)
{
    const int size = (opcode>>12==1 ? SIZE_B : opcode>>12==2 ? SIZE_L : SIZE_W);

    int cycles_src;
    ea_get(state, opcode, size, 0, &cycles_src, 1);
    if (cycles_src < 0) {
        return 1;
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

    /* Copy the operand to the result and set flags (if needed) */
    const int do_cc = cc_needed(state, opcode);
    if (EA_MODE(dummy_opcode) == EA_ADDRESS_REG) {
        if (size == SIZE_W) {
            JIT_EMIT_EXT_L(current_entry);
        } else {  // size == SIZE_L
            JIT_EMIT_MOVE_L(current_entry);
        }
    } else {
        if (size == SIZE_B) {
            JIT_EMIT_MOVE_B(current_entry);
            if (do_cc) JIT_EMIT_SETCC_LOGIC_B(current_entry);
        } else if (size == SIZE_W) {
            JIT_EMIT_MOVE_W(current_entry);
            if (do_cc) JIT_EMIT_SETCC_LOGIC_W(current_entry);
        } else {  // size == SIZE_L
            JIT_EMIT_MOVE_L(current_entry);
            if (do_cc) JIT_EMIT_SETCC_LOGIC_L(current_entry);
        }
    }

    /* Update the destination EA and cycle count */
    ea_set(state, dummy_opcode, size);
    JIT_EMIT_ADD_CYCLES(current_entry, 4 + cycles_src + cycles_dest);

    return 0;
}