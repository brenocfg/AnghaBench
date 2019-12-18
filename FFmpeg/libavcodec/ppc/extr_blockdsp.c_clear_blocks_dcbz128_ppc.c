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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_blocks_dcbz128_ppc(int16_t *blocks)
{
#if HAVE_DCBZL
    register int misal = (unsigned long) blocks & 0x0000007f, i = 0;

    if (misal) {
        /* We could probably also optimize this case,
         * but there's not much point as the machines
         * aren't available yet (2003-06-26). */
        memset(blocks, 0, sizeof(int16_t) * 6 * 64);
    } else {
        for (; i < sizeof(int16_t) * 6 * 64; i += 128)
            __asm__ volatile ("dcbzl %0,%1" :: "b" (blocks), "r" (i) : "memory");
    }
#else
    memset(blocks, 0, sizeof(int16_t) * 6 * 64);
#endif
}