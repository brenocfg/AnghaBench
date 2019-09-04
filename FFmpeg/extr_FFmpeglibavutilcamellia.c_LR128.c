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

__attribute__((used)) static void LR128(uint64_t d[2], const uint64_t K[2], int x)
{
    int i = 0;
    if (64 <= x && x < 128) {
        i = 1;
        x -= 64;
    }
    if (x <= 0 || x >= 128) {
        d[0] = K[i];
        d[1] = K[!i];
        return;
    }
    d[0] = (K[i] << x | K[!i] >> (64 - x));
    d[1] = (K[!i] << x | K[i] >> (64 - x));
}