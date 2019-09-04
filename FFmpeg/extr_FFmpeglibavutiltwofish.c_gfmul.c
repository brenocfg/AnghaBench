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

/* Variables and functions */

__attribute__((used)) static uint8_t gfmul(uint8_t a, uint8_t b)
{
    uint8_t r = 0, t;
    while (a && b) {
        if (a & 1)
            r = r ^ b;
        t = b & 0x80;
        b = b << 1;
        if (t)
            b = b ^ 0x4d;
        a = a >> 1;
    }
    return r;
}