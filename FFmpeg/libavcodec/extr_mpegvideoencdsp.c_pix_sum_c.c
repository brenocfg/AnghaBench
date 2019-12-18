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

__attribute__((used)) static int pix_sum_c(uint8_t *pix, int line_size)
{
    int s = 0, i, j;

    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j += 8) {
            s   += pix[0];
            s   += pix[1];
            s   += pix[2];
            s   += pix[3];
            s   += pix[4];
            s   += pix[5];
            s   += pix[6];
            s   += pix[7];
            pix += 8;
        }
        pix += line_size - 16;
    }
    return s;
}