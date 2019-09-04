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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */

int ff_startcode_find_candidate_c(const uint8_t *buf, int size)
{
    int i = 0;
#if HAVE_FAST_UNALIGNED
    /* we check i < size instead of i + 3 / 7 because it is
     * simpler and there must be AV_INPUT_BUFFER_PADDING_SIZE
     * bytes at the end.
     */
#if HAVE_FAST_64BIT
    while (i < size &&
            !((~*(const uint64_t *)(buf + i) &
                    (*(const uint64_t *)(buf + i) - 0x0101010101010101ULL)) &
                    0x8080808080808080ULL))
        i += 8;
#else
    while (i < size &&
            !((~*(const uint32_t *)(buf + i) &
                    (*(const uint32_t *)(buf + i) - 0x01010101U)) &
                    0x80808080U))
        i += 4;
#endif
#endif
    for (; i < size; i++)
        if (!buf[i])
            break;
    return i;
}