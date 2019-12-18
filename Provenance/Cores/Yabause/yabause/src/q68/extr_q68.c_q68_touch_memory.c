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
 int /*<<< orphan*/  JIT_PAGE_TEST (int /*<<< orphan*/ *,int) ; 
 int Q68_JIT_PAGE_BITS ; 
 scalar_t__ UNLIKELY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q68_jit_clear_page (int /*<<< orphan*/ *,int) ; 

void q68_touch_memory(Q68State *state, uint32_t address, uint32_t size)
{
#ifdef Q68_USE_JIT
    const uint32_t first_page = address >> Q68_JIT_PAGE_BITS;
    const uint32_t last_page = (address + (size-1)) >> Q68_JIT_PAGE_BITS;
    uint32_t page;
    for (page = first_page; page <= last_page; page++) {
        if (UNLIKELY(JIT_PAGE_TEST(state, page))) {
            q68_jit_clear_page(state, page << Q68_JIT_PAGE_BITS);
        }
    }
#endif
}