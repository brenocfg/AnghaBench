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
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t frac64(uint64_t a, uint64_t b)
{
    uint64_t r = 0;
    int i;

    if (b < (uint64_t)1 << 32) { /* b small, use two 32-bits steps */
        a <<= 32;
        return ((a / b) << 32) | ((a % b) << 32) / b;
    }
    if (b < (uint64_t)1 << 48) { /* b medium, use four 16-bits steps */
        for (i = 0; i < 4; i++) {
            a <<= 16;
            r = (r << 16) | (a / b);
            a %= b;
        }
        return r;
    }
    for (i = 63; i >= 0; i--) {
        if (a >= (uint64_t)1 << 63 || a << 1 >= b) {
            r |= (uint64_t)1 << i;
            a = (a << 1) - b;
        } else {
            a <<= 1;
        }
    }
    return r;
}