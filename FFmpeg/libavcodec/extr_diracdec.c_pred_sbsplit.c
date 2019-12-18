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

__attribute__((used)) static inline int pred_sbsplit(uint8_t *sbsplit, int stride, int x, int y)
{
    static const uint8_t avgsplit[7] = { 0, 0, 1, 1, 1, 2, 2 };

    if (!(x|y))
        return 0;
    else if (!y)
        return sbsplit[-1];
    else if (!x)
        return sbsplit[-stride];

    return avgsplit[sbsplit[-1] + sbsplit[-stride] + sbsplit[-stride-1]];
}