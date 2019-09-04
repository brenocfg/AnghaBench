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
typedef  int IDWTELEM ;

/* Variables and functions */

__attribute__((used)) static void horizontal_compose53i(IDWTELEM *b, IDWTELEM *temp, int width)
{
    const int width2 = width >> 1;
    const int w2     = (width + 1) >> 1;
    int x;

    for (x = 0; x < width2; x++) {
        temp[2 * x]     = b[x];
        temp[2 * x + 1] = b[x + w2];
    }
    if (width & 1)
        temp[2 * x] = b[x];

    b[0] = temp[0] - ((temp[1] + 1) >> 1);
    for (x = 2; x < width - 1; x += 2) {
        b[x]     = temp[x]     - ((temp[x - 1] + temp[x + 1] + 2) >> 2);
        b[x - 1] = temp[x - 1] + ((b[x - 2]    + b[x]        + 1) >> 1);
    }
    if (width & 1) {
        b[x]     = temp[x]     - ((temp[x - 1]     + 1) >> 1);
        b[x - 1] = temp[x - 1] + ((b[x - 2] + b[x] + 1) >> 1);
    } else
        b[x - 1] = temp[x - 1] + b[x - 2];
}