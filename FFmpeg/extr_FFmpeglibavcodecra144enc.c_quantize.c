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

__attribute__((used)) static int quantize(int value, const int16_t *table, unsigned int size)
{
    unsigned int low = 0, high = size - 1;

    while (1) {
        int index = (low + high) >> 1;
        int error = table[index] - value;

        if (index == low)
            return table[high] + error > value ? low : high;
        if (error > 0) {
            high = index;
        } else {
            low = index;
        }
    }
}