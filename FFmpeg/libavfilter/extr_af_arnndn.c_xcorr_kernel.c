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

__attribute__((used)) static inline void xcorr_kernel(const float *x, const float *y, float sum[4], int len)
{
    float y_0, y_1, y_2, y_3 = 0;
    int j;

    y_0 = *y++;
    y_1 = *y++;
    y_2 = *y++;

    for (j = 0; j < len - 3; j += 4) {
        float tmp;

        tmp = *x++;
        y_3 = *y++;
        sum[0] += tmp * y_0;
        sum[1] += tmp * y_1;
        sum[2] += tmp * y_2;
        sum[3] += tmp * y_3;
        tmp = *x++;
        y_0 = *y++;
        sum[0] += tmp * y_1;
        sum[1] += tmp * y_2;
        sum[2] += tmp * y_3;
        sum[3] += tmp * y_0;
        tmp = *x++;
        y_1 = *y++;
        sum[0] += tmp * y_2;
        sum[1] += tmp * y_3;
        sum[2] += tmp * y_0;
        sum[3] += tmp * y_1;
        tmp = *x++;
        y_2 = *y++;
        sum[0] += tmp * y_3;
        sum[1] += tmp * y_0;
        sum[2] += tmp * y_1;
        sum[3] += tmp * y_2;
    }

    if (j++ < len) {
        float tmp = *x++;

        y_3 = *y++;
        sum[0] += tmp * y_0;
        sum[1] += tmp * y_1;
        sum[2] += tmp * y_2;
        sum[3] += tmp * y_3;
    }

    if (j++ < len) {
        float tmp=*x++;

        y_0 = *y++;
        sum[0] += tmp * y_1;
        sum[1] += tmp * y_2;
        sum[2] += tmp * y_3;
        sum[3] += tmp * y_0;
    }

    if (j < len) {
        float tmp=*x++;

        y_1 = *y++;
        sum[0] += tmp * y_2;
        sum[1] += tmp * y_3;
        sum[2] += tmp * y_0;
        sum[3] += tmp * y_1;
    }
}