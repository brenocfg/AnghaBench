#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int* A; int fault_addr; int fault_status; int /*<<< orphan*/  exception; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  EX_ADDRESS_ERROR ; 
 int FAULT_STATUS_IN_DATA ; 
 int FAULT_STATUS_RW_READ ; 
 int /*<<< orphan*/  INSN_GET_REG0 ; 
 int READU32 (TYPE_1__*,int) ; 
 size_t reg0 ; 

__attribute__((used)) static int opUNLK(Q68State *state, uint32_t opcode)
{
    INSN_GET_REG0;
    /* FIXME: What happens if A7 is used as the register?  I.e. does the
     *        postincrement happen before or after the value is written to
     *        the destination register?  The Motorola docs could be read
     *        both ways, so going by the literal operation sequence here. */
    state->A[7] = state->A[reg0];
#ifndef Q68_DISABLE_ADDRESS_ERROR
    if (state->A[7] & 1) {
        state->exception = EX_ADDRESS_ERROR;
        state->fault_addr = state->A[7];
        state->fault_status = FAULT_STATUS_IN_DATA
                            | FAULT_STATUS_RW_READ;
        return 0;
    }
#endif
    state->A[reg0] = READU32(state, state->A[7]);
    state->A[7] += 4;
    return 12;
}