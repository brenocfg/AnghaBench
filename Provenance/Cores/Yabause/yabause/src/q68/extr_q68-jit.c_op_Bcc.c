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
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_5__ {int current_PC; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 scalar_t__ COND_EQ ; 
 scalar_t__ COND_F ; 
 scalar_t__ COND_PL ; 
 scalar_t__ COND_T ; 
 int FAULT_STATUS_IN_DATA ; 
 int FAULT_STATUS_RW_WRITE ; 
 scalar_t__ IFETCH (TYPE_1__*) ; 
 int /*<<< orphan*/  INSN_GET_COND ; 
 int /*<<< orphan*/  INSN_GET_DISP8 ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_BSR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_Bcc (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  JIT_EMIT_Bcc_native (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  JIT_EMIT_CHECK_ALIGNED_SP (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  JIT_EMIT_TEST_cc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  advance_PC (TYPE_1__*) ; 
 scalar_t__ btcache_lookup (int) ; 
 scalar_t__ cond ; 
 int /*<<< orphan*/  current_entry ; 
 scalar_t__ disp ; 
 int /*<<< orphan*/  jit_PC ; 
 int /*<<< orphan*/  record_unresolved_branch (int,scalar_t__) ; 

__attribute__((used)) static int op_Bcc(Q68State *state, uint32_t opcode)
{
    INSN_GET_COND;
    INSN_GET_DISP8;
    int cycles = 0;
    if (disp == 0) {
        disp = (int16_t)IFETCH(state);
        cycles = 4;
    }
    uint32_t target = state->current_PC + disp;
    if (cond == COND_F) {
        /* BF is really BSR */
#ifndef Q68_DISABLE_ADDRESS_ERROR
        JIT_EMIT_CHECK_ALIGNED_SP(current_entry, opcode,
                                  FAULT_STATUS_IN_DATA | FAULT_STATUS_RW_WRITE);
#endif
        JIT_EMIT_ADD_CYCLES(current_entry, 18);
        advance_PC(state);
        JIT_EMIT_BSR(current_entry, jit_PC, target);
        return 0;
    } else {
        int32_t offset;
#ifdef Q68_OPTIMIZE_IDLE
        /* FIXME: Temporary hack to improve PSP performance */
        if (target == 0x1066
         && ((cond == COND_EQ && state->current_PC - 2 == 0x001092)
          || (cond == COND_PL && state->current_PC - 2 == 0x0010B4))
        ) {
            /* BIOS intro animation */
            JIT_EMIT_ADD_CYCLES(current_entry,
                                468);  // Length of one loop when idle
        } else if (target == 0x10BC
                && ((cond == COND_PL && state->current_PC - 2 == 0x001122)
                 || (cond == COND_T  && state->current_PC - 2 == 0x00116A))
        ) {
            /* Azel: Panzer Dragoon RPG (JP) */
            JIT_EMIT_ADD_CYCLES(current_entry, 
                                178*4);  // Assuming a cycle_limit of 768
        }
#endif
        if (target < state->current_PC) {
            offset = btcache_lookup(target);
        } else {
            offset = -1;  // Forward jumps can't be in the cache
        }
        JIT_EMIT_TEST_cc(cond, current_entry);
        if (offset >= 0) {
            JIT_EMIT_Bcc_native(current_entry, target, offset);
        } else {
            int32_t branch_offset;
            JIT_EMIT_Bcc(current_entry, target, &branch_offset);
            if (target >= state->current_PC && branch_offset >= 0) {
                record_unresolved_branch(target, branch_offset);
            }
        }
        JIT_EMIT_ADD_CYCLES(current_entry, 8 + cycles);
        return 0;
    }
}