#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ m68k_start; } ;
struct TYPE_8__ {TYPE_2__* jit_table; int /*<<< orphan*/  (* free_func ) (TYPE_2__*) ;int /*<<< orphan*/ * jit_flush; int /*<<< orphan*/  jit_pages; TYPE_2__* jit_hashchain; TYPE_2__* (* malloc_func ) (int) ;} ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  DMSG (char*) ; 
 int /*<<< orphan*/  JIT_EMIT_CHECK_ALIGNED_EA (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_CHECK_ALIGNED_SP (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Q68_JIT_TABLE_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* stub1 (int) ; 
 TYPE_2__* stub2 (int) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 

int q68_jit_init(Q68State *state)
{
    state->jit_table =
        state->malloc_func(sizeof(*state->jit_table) * Q68_JIT_TABLE_SIZE);
    if (!state->jit_table) {
        DMSG("No memory for JIT table");
        goto error_return;
    }
    state->jit_hashchain =
        state->malloc_func(sizeof(*state->jit_hashchain) * Q68_JIT_TABLE_SIZE);
    if (!state->jit_hashchain) {
        DMSG("No memory for JIT hash chain table");
        goto error_free_jit_table;
    }

    /* Make sure all entries are marked as unused (so we don't try to free
     * invalid pointers in q68_jit_reset()) */
    int i;
    for (i = 0; i < Q68_JIT_TABLE_SIZE; i++) {
        state->jit_table[i].m68k_start = 0;
    }

    /* Make sure page table is clear (so writes before processor reset
     * don't trigger JIT clearing */
    memset(state->jit_pages, 0, sizeof(state->jit_pages));

    /* Default to no cache flush function */
    state->jit_flush   = NULL;

#ifdef Q68_DISABLE_ADDRESS_ERROR
    /* Hack to avoid compiler warnings about unused functions */
    if (0) {
        JIT_EMIT_CHECK_ALIGNED_EA(&state->jit_table[0], 0, 0);
        JIT_EMIT_CHECK_ALIGNED_SP(&state->jit_table[0], 0, 0);
    }
#endif

    return 1;

  error_free_jit_table:
    state->free_func(state->jit_table);
    state->jit_table = NULL;
  error_return:
    return 0;
}