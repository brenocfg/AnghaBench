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
typedef  int int16_t ;

/* Variables and functions */

__attribute__((used)) static int is_mv_diff_gt_3(int16_t (*motion_val)[2], int step)
{
    int d;
    d = motion_val[0][0] - motion_val[-step][0];
    if(d < -3 || d > 3)
        return 1;
    d = motion_val[0][1] - motion_val[-step][1];
    if(d < -3 || d > 3)
        return 1;
    return 0;
}