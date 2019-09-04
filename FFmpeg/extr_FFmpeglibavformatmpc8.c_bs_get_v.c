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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int int64_t ;

/* Variables and functions */

__attribute__((used)) static inline int64_t bs_get_v(const uint8_t **bs)
{
    uint64_t v = 0;
    int br = 0;
    int c;

    do {
        c = **bs; (*bs)++;
        v <<= 7;
        v |= c & 0x7F;
        br++;
        if (br > 10)
            return -1;
    } while (c & 0x80);

    return v - br;
}