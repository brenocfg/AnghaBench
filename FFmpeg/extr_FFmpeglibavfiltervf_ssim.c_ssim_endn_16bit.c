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
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ ssim_end1x (scalar_t__ const,scalar_t__ const,scalar_t__ const,scalar_t__ const,int) ; 

__attribute__((used)) static float ssim_endn_16bit(const int64_t (*sum0)[4], const int64_t (*sum1)[4], int width, int max)
{
    float ssim = 0.0;
    int i;

    for (i = 0; i < width; i++)
        ssim += ssim_end1x(sum0[i][0] + sum0[i + 1][0] + sum1[i][0] + sum1[i + 1][0],
                           sum0[i][1] + sum0[i + 1][1] + sum1[i][1] + sum1[i + 1][1],
                           sum0[i][2] + sum0[i + 1][2] + sum1[i][2] + sum1[i + 1][2],
                           sum0[i][3] + sum0[i + 1][3] + sum1[i][3] + sum1[i + 1][3],
                           max);
    return ssim;
}