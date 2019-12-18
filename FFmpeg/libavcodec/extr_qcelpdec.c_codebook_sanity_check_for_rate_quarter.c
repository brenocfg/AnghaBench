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
 int FFABS (int) ; 

__attribute__((used)) static int codebook_sanity_check_for_rate_quarter(const uint8_t *cbgain)
{
    int i, diff, prev_diff = 0;

    for (i = 1; i < 5; i++) {
        diff = cbgain[i] - cbgain[i-1];
        if (FFABS(diff) > 10)
            return -1;
        else if (FFABS(diff - prev_diff) > 12)
            return -1;
        prev_diff = diff;
    }
    return 0;
}