#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_14__ {int running; int /*<<< orphan*/  exec_address; int /*<<< orphan*/  must_clear; int /*<<< orphan*/  timestamp; } ;
struct TYPE_13__ {scalar_t__ cycles; unsigned int jit_callstack_top; scalar_t__ PC; int /*<<< orphan*/  exception; TYPE_1__* jit_callstack; int /*<<< orphan*/ * A; scalar_t__ jit_abort; int /*<<< orphan*/  jit_timestamp; } ;
struct TYPE_12__ {scalar_t__ return_PC; int /*<<< orphan*/  return_native; TYPE_3__* return_entry; } ;
typedef  TYPE_2__ Q68State ;
typedef  TYPE_3__ Q68JitEntry ;

/* Variables and functions */
 int JIT_CALL (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *) ; 
 unsigned int Q68_JIT_CALLSTACK_SIZE ; 
 scalar_t__ READU32 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ UNLIKELY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_entry (TYPE_2__*,TYPE_3__*) ; 
 TYPE_3__* q68_jit_find (TYPE_2__*,scalar_t__) ; 

void q68_jit_run(Q68State *state, uint32_t cycle_limit,
                 Q68JitEntry **entry_ptr)
{
    Q68JitEntry *entry = *entry_ptr;

  again:
    entry->timestamp = state->jit_timestamp;
    state->jit_timestamp++;
    entry->running = 1;
    int cycles = JIT_CALL(state, cycle_limit - state->cycles,
                          &entry->exec_address);
    entry->running = 0;
    state->jit_abort = 0;
    state->cycles += cycles & 0x3FFF;

    if (UNLIKELY(entry->must_clear)) {
        clear_entry(state, entry);
        entry = NULL;
    } else if (cycles & 0x8000) {  // BSR/JSR/RTS/RTR
        if (cycles & 0x4000) {  // RTS/RTR
            entry = NULL;
            unsigned int top = state->jit_callstack_top;
            unsigned int i;
            for (i = Q68_JIT_CALLSTACK_SIZE; i > 0; i--) {
                top = (top + Q68_JIT_CALLSTACK_SIZE-1) % Q68_JIT_CALLSTACK_SIZE;
                if (state->jit_callstack[top].return_PC == state->PC) {
                    entry = state->jit_callstack[top].return_entry;
                    entry->exec_address =
                        state->jit_callstack[top].return_native;
                    state->jit_callstack_top = top;
                    if (state->cycles < cycle_limit) {
                        goto again;
                    } else {
                        break;
                    }
                }
            }
        } else {  // BSR/JSR
            const unsigned int top = state->jit_callstack_top;
            const uint32_t return_PC = READU32(state, state->A[7]);
            state->jit_callstack[top].return_PC = return_PC;
            state->jit_callstack[top].return_entry = entry;
            state->jit_callstack[top].return_native = entry->exec_address;
            state->jit_callstack_top = (top+1) % Q68_JIT_CALLSTACK_SIZE;
            entry = NULL;
        }
    } else if (!entry->exec_address) {
        entry = NULL;
    }

    /* If we finished a block, we still have cycles to go, there's no
     * exception pending, and there's already a translated block at the
     * next PC, jump right to it so we don't incur the extra overhead of
     * returning to the caller */
    if (!entry && state->cycles < cycle_limit && !state->exception) {
        entry = q68_jit_find(state, state->PC);
        if (entry) {
            goto again;
        }
    }

    *entry_ptr = entry;
}