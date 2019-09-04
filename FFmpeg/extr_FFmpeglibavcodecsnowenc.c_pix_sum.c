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

__attribute__((used)) static int pix_sum(uint8_t * pix, int line_size, int w, int h)
{
    int s, i, j;

    s = 0;
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            s += pix[0];
            pix ++;
        }
        pix += line_size - w;
    }
    return s;
}