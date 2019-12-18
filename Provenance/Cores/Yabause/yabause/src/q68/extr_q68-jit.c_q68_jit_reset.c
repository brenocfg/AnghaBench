#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ m68k_start; } ;
struct TYPE_7__ {int /*<<< orphan*/  jit_pages; scalar_t__ jit_callstack_top; scalar_t__ jit_blist_num; scalar_t__ jit_in_blist; TYPE_1__* jit_blacklist; scalar_t__ jit_timestamp; scalar_t__ jit_total_data; int /*<<< orphan*/ ** jit_hashchain; TYPE_5__* jit_table; scalar_t__ jit_abort; } ;
struct TYPE_6__ {scalar_t__ m68k_end; scalar_t__ m68k_start; } ;
typedef  TYPE_2__ Q68State ;

/* Variables and functions */
 int Q68_JIT_BLACKLIST_SIZE ; 
 int Q68_JIT_TABLE_SIZE ; 
 int /*<<< orphan*/  clear_entry (TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void q68_jit_reset(Q68State *state)
{
    int index;

    state->jit_abort = 0;
    for (index = 0; index < Q68_JIT_TABLE_SIZE; index++) {
        if (state->jit_table[index].m68k_start) {
            clear_entry(state, &state->jit_table[index]);
        }
    }
    for (index = 0; index < Q68_JIT_TABLE_SIZE; index++) {
        state->jit_hashchain[index] = NULL;
    }
    state->jit_total_data = 0;
    state->jit_timestamp = 0;
    for (index = 0; index < Q68_JIT_BLACKLIST_SIZE; index++) {
        state->jit_blacklist[index].m68k_start = 0;
        state->jit_blacklist[index].m68k_end = 0;
    }
    state->jit_in_blist = 0;
    state->jit_blist_num = 0;
    state->jit_callstack_top = 0;
    memset(state->jit_pages, 0, sizeof(state->jit_pages));
}