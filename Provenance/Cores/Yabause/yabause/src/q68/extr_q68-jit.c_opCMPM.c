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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  Q68State ;

/* Variables and functions */
 int EA_POSTINCREMENT ; 
 int /*<<< orphan*/  INSN_GET_REG ; 
 int /*<<< orphan*/  INSN_GET_REG0 ; 
 int /*<<< orphan*/  INSN_GET_SIZE ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_CMP_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_CMP_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_CMP_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SUB_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SUB_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SUB_W (int /*<<< orphan*/ ) ; 
 scalar_t__ SIZE_B ; 
 scalar_t__ SIZE_L ; 
 scalar_t__ SIZE_W ; 
 int cc_needed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_entry ; 
 int /*<<< orphan*/  ea_get (int /*<<< orphan*/ *,int const,scalar_t__,int /*<<< orphan*/ ,int*,int) ; 
 int reg ; 
 int reg0 ; 
 scalar_t__ size ; 

__attribute__((used)) static int opCMPM(Q68State *state, uint32_t opcode)
{
    INSN_GET_REG;
    INSN_GET_SIZE;
    INSN_GET_REG0;

    const uint16_t src_ea  = EA_POSTINCREMENT<<3 | reg0;
    const uint16_t dest_ea = EA_POSTINCREMENT<<3 | reg;
    int dummy;
    ea_get(state, src_ea,  size, 0, &dummy, 1);
    ea_get(state, dest_ea, size, 0, &dummy, 2);

    const int do_cc = cc_needed(state, opcode);  // Just for consistency
    if (size == SIZE_B) {
        JIT_EMIT_SUB_B(current_entry);
        if (do_cc) JIT_EMIT_SETCC_CMP_B(current_entry);
    } else if (size == SIZE_W) {
        JIT_EMIT_SUB_W(current_entry);
        if (do_cc) JIT_EMIT_SETCC_CMP_W(current_entry);
    } else {  // size == SIZE_L
        JIT_EMIT_SUB_L(current_entry);
        if (do_cc) JIT_EMIT_SETCC_CMP_L(current_entry);
    }

    JIT_EMIT_ADD_CYCLES(current_entry, SIZE_L ? 20 : 12);
    return 0;
}