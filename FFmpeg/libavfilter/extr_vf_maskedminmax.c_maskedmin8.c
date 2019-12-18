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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ FFABS (scalar_t__ const) ; 

__attribute__((used)) static void maskedmin8(const uint8_t *src, uint8_t *dst, const uint8_t *f1, const uint8_t *f2, int w)
{
    for (int x = 0; x < w; x++)
        dst[x] = FFABS(src[x] - f2[x]) < FFABS(src[x] - f1[x]) ? f2[x] : f1[x];
}