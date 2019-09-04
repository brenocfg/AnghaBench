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

__attribute__((used)) static int find_index(int *index, int value, int size)
{
    int i, start, end;

    if ((value < index[0]) || (value > index[size - 1]))
        return 1;

    i = start = 0;
    end = size - 1;

    while (start <= end) {
        i = (end + start) / 2;
        if (index[i] == value)
            return 0;
        if (value < index[i])
            end = i - 1;
        if (value > index[i])
            start = i + 1;
    }

    return 1;
}