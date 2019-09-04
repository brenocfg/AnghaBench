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
typedef  int int64_t ;

/* Variables and functions */
 int* exp16_table ; 

__attribute__((used)) static int64_t log16(uint64_t a)
{
    int i;
    int out = 0;

    if (a < 1 << 16)
        return -log16((1LL << 32) / a);
    a <<= 16;

    for (i = 20; i >= 0; i--) {
        int64_t b = exp16_table[i];
        if (a < (b << 16))
            continue;
        out |= 1 << i;
        a    = ((a / b) << 16) + (((a % b) << 16) + b / 2) / b;
    }
    return out;
}