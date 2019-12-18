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
typedef  float uint8_t ;

/* Variables and functions */

__attribute__((used)) static void pixel2float48(const uint8_t *t8, const int pitch, float *p)
{
    const uint8_t *t = (const uint8_t *)t8;
    int y, x;

    for (y = 0; y < 4; y++)
        for (x = 0; x < 12; x++)
            p[y * 12 + x] = t[y * pitch * 2 + x];
}