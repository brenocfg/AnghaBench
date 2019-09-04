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

__attribute__((used)) static uint64_t int_sqrt(uint64_t a)
{
    uint64_t ret    = 0;
    uint64_t ret_sq = 0;
    int s;

    for (s = 31; s >= 0; s--) {
        uint64_t b = ret_sq + (1ULL << (s * 2)) + (ret << s) * 2;
        if (b <= a) {
            ret_sq = b;
            ret   += 1ULL << s;
        }
    }
    return ret;
}