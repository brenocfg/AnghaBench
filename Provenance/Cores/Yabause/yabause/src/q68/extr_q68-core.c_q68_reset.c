#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ halted; void* PC; void** A; int /*<<< orphan*/ * jit_running; scalar_t__ fault_status; scalar_t__ fault_opcode; scalar_t__ fault_addr; scalar_t__ exception; scalar_t__ ea_addr; scalar_t__ current_PC; scalar_t__ SSP; scalar_t__ USP; int /*<<< orphan*/  SR; scalar_t__* D; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 void* READU32 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  SR_S ; 
 int /*<<< orphan*/  SR_SET_I (TYPE_1__*,int) ; 
 int /*<<< orphan*/  q68_jit_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  q68_trace_init (TYPE_1__*) ; 

void q68_reset(Q68State *state)
{
    int i;
    for (i = 0; i < 8; i++) {
        state->D[i] = 0;
        state->A[i] = 0;
    }
    state->PC = 0;
    state->SR = SR_S;
    SR_SET_I(state, 7);
    state->USP = 0;
    state->SSP = 0;
    state->current_PC = 0;
    state->ea_addr = 0;
    state->exception = 0;
    state->fault_addr = 0;
    state->fault_opcode = 0;
    state->fault_status = 0;
    state->jit_running = NULL;
#ifdef Q68_USE_JIT
    q68_jit_reset(state);
#endif
#ifdef Q68_TRACE
    q68_trace_init(state);
#endif

    state->A[7] = READU32(state, 0x000000);
    state->PC = READU32(state, 0x000004);
    state->halted = 0;
}