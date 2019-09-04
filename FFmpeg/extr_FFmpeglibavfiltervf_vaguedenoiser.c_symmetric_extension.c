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

/* Variables and functions */
 int NPAD ; 

__attribute__((used)) static void symmetric_extension(float *output, const int size, const int left_ext, const int right_ext)
{
    int first = NPAD;
    int last = NPAD - 1 + size;
    const int originalLast = last;
    int i, nextend, idx;

    if (left_ext == 2)
        output[--first] = output[NPAD];
    if (right_ext == 2)
        output[++last] = output[originalLast];

    // extend left end
    nextend = first;
    for (i = 0; i < nextend; i++)
        output[--first] = output[NPAD + 1 + i];

    idx = NPAD + NPAD - 1 + size;

    // extend right end
    nextend = idx - last;
    for (i = 0; i < nextend; i++)
        output[++last] = output[originalLast - 1 - i];
}