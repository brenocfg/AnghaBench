#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int const uint32_t ;
struct TYPE_7__ {int m68k_start; int m68k_end; int must_clear; int /*<<< orphan*/  running; } ;
struct TYPE_6__ {int jit_abort; TYPE_4__* jit_table; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  DMSG (char*,int const) ; 
 int /*<<< orphan*/  JIT_PAGE_CLEAR (TYPE_1__*,int const) ; 
 int const Q68_JIT_PAGE_BITS ; 
 int Q68_JIT_TABLE_SIZE ; 
 scalar_t__ UNLIKELY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_entry (TYPE_1__*,TYPE_4__*) ; 

void q68_jit_clear_page(Q68State *state, uint32_t address)
{
    const uint32_t page = address >> Q68_JIT_PAGE_BITS;
#ifdef Q68_JIT_VERBOSE
    DMSG("WARNING: jit_clear_page($%06X)", page << Q68_JIT_PAGE_BITS);
#endif

    int index;
    for (index = 0; index < Q68_JIT_TABLE_SIZE; index++) {
        if (state->jit_table[index].m68k_start != 0
         && state->jit_table[index].m68k_start >> Q68_JIT_PAGE_BITS <= page
         && state->jit_table[index].m68k_end   >> Q68_JIT_PAGE_BITS >= page
        ) {
            if (UNLIKELY(state->jit_table[index].running)) {
                state->jit_table[index].must_clear = 1;
                state->jit_abort = 1;
            } else {
                clear_entry(state, &state->jit_table[index]);
            }
        }
    }

    JIT_PAGE_CLEAR(state, page);
}