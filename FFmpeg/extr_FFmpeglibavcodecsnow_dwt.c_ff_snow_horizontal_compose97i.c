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

void ff_snow_horizontal_compose97i(IDWTELEM *b, IDWTELEM *temp, int width)
{
    const int w2 = (width + 1) >> 1;
    int x;

    temp[0] = b[0] - ((3 * b[w2] + 2) >> 2);
    for (x = 1; x < (width >> 1); x++) {
        temp[2 * x]     = b[x] - ((3 * (b[x + w2 - 1] + b[x + w2]) + 4) >> 3);
        temp[2 * x - 1] = b[x + w2 - 1] - temp[2 * x - 2] - temp[2 * x];
    }
    if (width & 1) {
        temp[2 * x]     = b[x] - ((3 * b[x + w2 - 1] + 2) >> 2);
        temp[2 * x - 1] = b[x + w2 - 1] - temp[2 * x - 2] - temp[2 * x];
    } else
        temp[2 * x - 1] = b[x + w2 - 1] - 2 * temp[2 * x - 2];

    b[0] = temp[0] + ((2 * temp[0] + temp[1] + 4) >> 3);
    for (x = 2; x < width - 1; x += 2) {
        b[x]     = temp[x] + ((4 * temp[x] + temp[x - 1] + temp[x + 1] + 8) >> 4);
        b[x - 1] = temp[x - 1] + ((3 * (b[x - 2] + b[x])) >> 1);
    }
    if (width & 1) {
        b[x]     = temp[x] + ((2 * temp[x] + temp[x - 1] + 4) >> 3);
        b[x - 1] = temp[x - 1] + ((3 * (b[x - 2] + b[x])) >> 1);
    } else
        b[x - 1] = temp[x - 1] + 3 * b[x - 2];
}