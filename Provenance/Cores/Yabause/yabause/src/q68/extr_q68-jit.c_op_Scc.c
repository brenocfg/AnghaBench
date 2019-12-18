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
 int /*<<< orphan*/  ACCESS_MODIFY ; 
 scalar_t__ EA_ADDRESS_REG ; 
 scalar_t__ EA_DATA_REG ; 
 scalar_t__ EA_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_GET_COND ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES_Scc_Dn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_Scc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_TEST_cc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIZE_B ; 
 int /*<<< orphan*/  cond ; 
 int /*<<< orphan*/  current_entry ; 
 int ea_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ea_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int opDBcc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int op_ill (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int op_Scc(Q68State *state, uint32_t opcode)
{
    if (EA_MODE(opcode) == EA_ADDRESS_REG) {
        /* DBcc Dn,disp is coded as Scc An with an extension word */
        return opDBcc(state, opcode);
    }

    INSN_GET_COND;
    /* From the cycle counts, it looks like this is a standard read/write
     * access rather than a write-only access */
    int cycles;
    if (EA_MODE(opcode) == EA_DATA_REG) {
        cycles = 0;
    } else {
        cycles = ea_resolve(state, opcode, SIZE_B, ACCESS_MODIFY);
        if (cycles < 0) {
            return op_ill(state, opcode);
        }
    }
    JIT_EMIT_TEST_cc(cond, current_entry);
    JIT_EMIT_Scc(current_entry);
    if (EA_MODE(opcode) == EA_DATA_REG) {
        /* Scc Dn is a special case */
        JIT_EMIT_ADD_CYCLES_Scc_Dn(current_entry);
    } else {
        JIT_EMIT_ADD_CYCLES(current_entry, 8 + cycles);
    }
    ea_set(state, opcode, SIZE_B);
    return 0;
}