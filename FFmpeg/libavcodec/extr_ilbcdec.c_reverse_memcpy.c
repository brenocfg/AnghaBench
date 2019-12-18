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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */

__attribute__((used)) static void reverse_memcpy(int16_t *dest, int16_t *source, int length)
{
    int16_t* destPtr = dest;
    int16_t* sourcePtr = source;
    int j;

    for (j = 0; j < length; j++)
        *destPtr-- = *sourcePtr++;
}