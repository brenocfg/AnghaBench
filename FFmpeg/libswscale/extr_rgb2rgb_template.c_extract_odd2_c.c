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

__attribute__((used)) static void extract_odd2_c(const uint8_t *src, uint8_t *dst0, uint8_t *dst1,
                           int count)
{
    dst0  +=  count;
    dst1  +=  count;
    src   +=  count * 4;
    count  = -count;
    src++;
    while (count < 0) {
        dst0[count] = src[4 * count + 0];
        dst1[count] = src[4 * count + 2];
        count++;
    }
}