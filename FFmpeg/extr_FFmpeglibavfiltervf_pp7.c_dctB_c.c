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
typedef  int int16_t ;

/* Variables and functions */

__attribute__((used)) static void dctB_c(int16_t *dst, int16_t *src)
{
    int i;

    for (i = 0; i < 4; i++) {
        int s0 = src[0 * 4] + src[6 * 4];
        int s1 = src[1 * 4] + src[5 * 4];
        int s2 = src[2 * 4] + src[4 * 4];
        int s3 = src[3 * 4];
        int s = s3 + s3;
        s3 = s  - s0;
        s0 = s  + s0;
        s  = s2 + s1;
        s2 = s2 - s1;
        dst[0 * 4] = s0 + s;
        dst[2 * 4] = s0 - s;
        dst[1 * 4] = 2 * s3 +     s2;
        dst[3 * 4] =     s3 - 2 * s2;
        src++;
        dst++;
    }
}