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
 scalar_t__ FFABS (int) ; 

__attribute__((used)) static void fill_l1distlut(uint8_t lut[])
{
    int i, j, tmp_i, tmp_j,count;
    uint8_t dist;

    for (i = 0, count = 0; i < 242; i++) {
        for (j = i + 1; j < 243; j++, count++) {
            /* ternary distance between i and j */
            dist = 0;
            tmp_i = i; tmp_j = j;
            do {
                dist += FFABS((tmp_j % 3) - (tmp_i % 3));
                tmp_j /= 3;
                tmp_i /= 3;
            } while (tmp_i > 0 || tmp_j > 0);
            lut[count] = dist;
        }
    }
}