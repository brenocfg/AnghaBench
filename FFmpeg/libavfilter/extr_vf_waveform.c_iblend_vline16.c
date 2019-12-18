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
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static void iblend_vline16(uint8_t *ddst, int height, int linesize, float o1, float o2, int v, int step)
{
    uint16_t *dst = (uint16_t *)ddst;
    int y;

    for (y = 0; y < height; y += step) {
        dst[0] = (v - dst[0]) * o1 + dst[0] * o2;

        dst += (linesize / 2) * step;
    }
}